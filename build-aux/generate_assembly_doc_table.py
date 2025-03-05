from bs4 import BeautifulSoup
from cached_requests import cached_get

BASE_URL="https://www.felixcloutier.com"

def get_instructions():
    response = cached_get(BASE_URL + "/x86/")
    response.raise_for_status()
    return response.content

instructions = get_instructions()
soup = BeautifulSoup(instructions, "html.parser")

_h2 = soup.find('h2', string='Core Instructions')
table = _h2.find_next_sibling('table')

instructions = [
    (a_tag.text, a_tag['href'])
    for a_tag in table.find_all('a', href=True)
]

for i in instructions:
    response = cached_get(BASE_URL + i[1])
    response.raise_for_status()

    