import clang.cindex
from bs4 import BeautifulSoup
from cached_requests import cached_get

class SomethingWentWrong(BaseException):
    def __init__(self):
        super().__init__(":(")

def get_instructions():
    response = cached_get("https://www.felixcloutier.com/x86/")
    response.raise_for_status()
    return response.content

def find_inline_asm(source_file):
    # Initialize clang index
    index = clang.cindex.Index.create()
    
    # Parse the file into an AST
    translation_unit = index.parse(source_file, args=['-x', 'c', '-I../../include'])  # Ensure Clang treats it as C code

    # Traverse the AST
    for node in translation_unit.cursor.walk_preorder():
        if node.location.file and node.location.file.name == source_file:
            print(node.spelling, str(node.kind))
            if node.kind == clang.cindex.CursorKind.ASM_STMT:  # Inline assembly statement
                asm_tokens = [t.spelling for t in node.get_tokens() if (t.spelling[0] == "\"" and t.spelling[-3:] == "\\n\"")]
                asm_code = "\n--> ".join(asm_tokens)  # Join tokens into a readable string
                print(f"Assembly: {asm_code}")

instructions = get_instructions()
soup = BeautifulSoup(instructions, "html.parser")

_h2 = soup.find('h2', string='Core Instructions')
table = _h2.find_next_sibling('table')

instructions = [
    (a_tag.text, a_tag['href'])
    for a_tag in table.find_all('a', href=True)
]

for i in instructions:
    print(i[0], i[1])