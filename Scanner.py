import re

keywords = {"int", "if", "return", "char", "double", "while"}
operators = r"[+\-*/=<>!]+"
punctuation = r"[;,\(\)\{\}]"
identifier = r"[a-zA-Z_]\w*"
numeric_constant = r"\b\d+(\.\d+)?\b"
character_constant = r"'(\\.|[^\\'])'"  
whitespace = r"[ \t]+"
newline = r"\n"

code = """int x = 10;  
char ch = 'A';
if (x > 0) x = x + 1;
double y = 3.14;
while (x < 100) x++;"""

tokens = []

position = 0
while position < len(code):
    match = None

    if match := re.match(identifier, code[position:]):
        text = match.group()
        if text in keywords:
            tokens.append(('KEYWORD', text))
        else:
            tokens.append(('IDENTIFIER', text))

    elif match := re.match(numeric_constant, code[position:]):
        tokens.append(('NUMERIC_CONSTANT', match.group()))

    elif match := re.match(character_constant, code[position:]):
        tokens.append(('CHARACTER_CONSTANT', match.group()))

    elif match := re.match(operators, code[position:]):
        tokens.append(('OPERATOR', match.group()))

    elif match := re.match(punctuation, code[position:]):
        tokens.append(('PUNCTUATION', match.group()))

    elif match := re.match(newline, code[position:]):
        tokens.append(('NEWLINE', '\\n'))

    elif match := re.match(whitespace, code[position:]):
        tokens.append(('WHITESPACE', match.group()))

    if match:
        position += len(match.group())
    else:
        position += 1

for token in tokens:
    print(token)
