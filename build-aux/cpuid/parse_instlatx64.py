from cached_requests import cached_get_selenium
from bs4 import BeautifulSoup
import re

instlatx64_content = cached_get_selenium("https://users.atw.hu/instlatx64/")

soup = BeautifulSoup(instlatx64_content, "html.parser")
lst = soup.find("body").find("pre")
txt = str(lst)

vendors = {}
curr = []
for l in txt.splitlines():
    l = l.strip()
    if l == "<pre>":
        continue

    groups = re.match(r"<u><b>([\w ]+)</b></u>", l)
    if groups is not None:
        curr = []
        vendors[groups[1]] = curr
        continue
    
    chunks = [BeautifulSoup(c, "html.parser").get_text(strip=True) for c in l.split("   ")]
    curr.append(' '.join(chunks))

for k in vendors.keys():
    print(f"Vendor: {k}")
    for entry in vendors[k]:
        print(f"\t{entry}")
