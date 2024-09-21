# Token types
TOKENS = {
    'PROGRAM': 'program',
    'BEGIN': 'begin',
    'END': 'end',
    'INT': 'int',
    'DOUBLE': 'double',
    'PRINT': 'print',
    'ASSIGN': '=',
    'SEMICOLON': ';',
    'COMMA': ',',
    'PLUS': '+',
    'MINUS': '-',
    'MULT': '*',
    'DIV': '/',
    'POW': '^',
    'LPAREN': '(',
    'RPAREN': ')',
    'ID': r'[a-zA-Z]',
    'NUM': r'[0-9]+',
}

# A class to hold the symbol table entries (id, type, value)
class SymbolTableEntry:
    def __init__(self, id_name, id_type, value=None):
        self.id_name = id_name
        self.id_type = id_type
        self.value = value

# A symbol table as a dictionary
symbol_table = {}

# Parser functions (recursive descent)
def parse_prog(tokens):
    # Handle <Prog> ::= program <Declarations> begin <Statements> end
    if tokens.pop(0) != 'program':
        raise SyntaxError("Expected 'program'")
    parse_declarations(tokens)
    if tokens.pop(0) != 'begin':
        raise SyntaxError("Expected 'begin'")
    parse_statements(tokens)
    if tokens.pop(0) != 'end':
        raise SyntaxError("Expected 'end'")

def parse_declarations(tokens):
    # Recursive function to handle <Declarations>
    # <Declarations> ::= <Declaration> | <Declaration> <Declarations> | e
    while tokens[0] in ['int', 'double']:
        parse_declaration(tokens)

def parse_declaration(tokens):
    # Handle <Declaration> ::= <Type> <Id-list> ;
    var_type = tokens.pop(0)  # int or double
    while True:
        var_name = tokens.pop(0)  # should be an ID
        if var_name.isalpha():
            symbol_table[var_name] = SymbolTableEntry(var_name, var_type)
        else:
            raise SyntaxError(f"Invalid identifier: {var_name}")
        if tokens[0] == ';':
            tokens.pop(0)
            break
        elif tokens[0] == ',':
            tokens.pop(0)
        else:
            raise SyntaxError("Expected ',' or ';'")

def parse_statements(tokens):
    # Recursive function to handle <Statements>
    # <Statements> ::= <Statement> <Statements> | e
    while tokens[0] != 'end':
        parse_statement(tokens)

def parse_statement(tokens):
    # Handle either assignment or print statement
    if tokens[0] == 'print':
        parse_print_statement(tokens)
    elif tokens[0].isalpha():
        parse_assign_statement(tokens)
    else:
        raise SyntaxError("Expected 'print' or identifier")

def parse_assign_statement(tokens):
    # Handle <Assign-St> ::= <Id> = <Exp> ;
    var_name = tokens.pop(0)  # should be an ID
    if tokens.pop(0) != '=':
        raise SyntaxError("Expected '='")
    value = parse_exp(tokens)
    if tokens.pop(0) != ';':
        raise SyntaxError("Expected ';'")
    symbol_table[var_name].value = value

def parse_print_statement(tokens):
    # Handle <Print-St> ::= print <Id> ; or print <Exp> ;
    tokens.pop(0)  # remove 'print'
    if tokens[0].isalpha():
        var_name = tokens.pop(0)
        if var_name in symbol_table:
            print(symbol_table[var_name].value)
        else:
            raise SemanticError(f"Undeclared variable: {var_name}")
    else:
        value = parse_exp(tokens)
        print(value)
    if tokens.pop(0) != ';':
        raise SyntaxError("Expected ';'")

def parse_exp(tokens):
    # Handle expression parsing: <Exp> ::= <Term> <Exp2>
    # Add logic to evaluate the expression and return its result
    pass  # Recursive parsing for expressions here

# Error handling classes
class LexicalError(Exception): pass
class SyntaxError(Exception): pass
class SemanticError(Exception): pass

# Main function to run the interpreter
def run_fresno_f24_program(program_code):
    tokens = tokenize(program_code)
    parse_prog(tokens)

def tokenize(program_code):
    # A simple tokenizer to break the input code into tokens
    return program_code.split()

# Example usage:
fresno_code = """
program
    int a, b, c;
    double d;
    begin
        a = 2*(55+200);
        b = (31 + 4) * 50;
        c = a;
        print a;
        print b;
        print c;
        print (2+300/2)*4 + 2^3;
    end
"""
run_fresno_f24_program(fresno_code)
