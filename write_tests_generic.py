import re

with open("./libft.h", "r") as f:
    header = f.read()
    
matches = re.findall("extern\s*[a-zA-Z0-9_]*\s*[\*]*?ft_([a-zA-Z0-9_]*)", header)
for m in matches:
    

