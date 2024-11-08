import re

# Define token types
keywords = {"int", "if", "return","for", "char", "double", "while","void","float"}
operators = r"[+\-*/=<>!]+"
punctuation = r"[;,\(\)\{\}]"
identifier = r"[a-zA-Z_]\w*"
numeric_constant = r"\b\d+(\.\d+)?\b"
character_constant = r"'(\\.|[^\\'])'"
whitespace = r"[ \t]+"
newline = r"\n"
single_line_comment = r"//[^\n]*"
multi_line_comment = r"/\[\s\S]?\*/"

# Request code input from the user
code = input("Enter the C code you want to scan:\n")

tokens = []

position = 0
while position < len(code):
    match = None
    if match := re.match(single_line_comment, code[position:]):
        tokens.append(('SINGLE_LINE_COMMENT', match.group()))
        
    elif match := re.match(multi_line_comment, code[position:]):
        tokens.append(('MULTI_LINE_COMMENT', match.group()))
    elif match := re.match(identifier, code[position:]):
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

# Print the tokens
for token in tokens:
    print(token)