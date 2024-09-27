//! program is stored in "input.txt". path can be changed in main

// Interpreter for simplified infix expression with {+, -, *, /, ^ } operations;
// Keyboard input, single digit numbers only and no spaces are allowed;
// compile: $> g++ assignment4.cpp
// run with: 2+3*4/2+3+4*2 or (3+2)*2^3

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cctype>
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Power(), Power2(int);
void Declarations(), Declaration(string), Statements(), Statement(string), print_st(), assign_st(string);

// helper funcitons
void loadProgram(string), startProgram(), printSymbolTable();
string readWord();
int findSymbolById(char);

string prog;    // string for reading 1-line input expression (program)
int indexx = 0; // global indexx for program string
struct symbol   // stores information about a symbol
{
    char id;
    string type;
    int val;
};
vector<symbol> symbol_table; // stores all symbols

int main(int argc, const char **argv)
{
    string path = "input.txt";

    loadProgram(path);
    startProgram();
    printSymbolTable();
    return 0;
}

void loadProgram(string path)
{
    // Open file
    ifstream inputFile(path);
    if (!inputFile)
    {
        cerr << "Error opening input file!" << endl;
        exit(1);
    }

    // Read input from file
    char ch;
    while (inputFile.get(ch))
    {
        prog += ch;
    }
    cout << endl
         << prog << endl
         << endl;
}

void startProgram()
{
    cout << "---PROGRAM OUTPUT---" << endl;
    string word = readWord();
    if (word == "program")
    {
        Declarations();
        Statements();
    }
    else
    {
        cerr << "startProgram Error: No program found" << endl;
        exit(1);
    }
}

// read word will read the next word of the program
// for example, "print", "a", and ";" are words
// "print;" is considered two words, "print" and ";"
string readWord()
{
    string word = "";
    while (isspace(prog[indexx])) // remove leading whitespace
        indexx++;

    // special case: semicolon
    if (prog[indexx] == ';' || prog[indexx] == ',')
    {
        word = prog[indexx];
        indexx++;
    }
    else // read word
    {
        while (!isspace(prog[indexx]) && prog[indexx] != '\0' && prog[indexx] != ';' && prog[indexx] != ',')
        {
            word += prog[indexx];
            indexx++;
        }
    }

    while (isspace(prog[indexx])) // remove trailing white space
        indexx++;

    return word;
}

// read a list of statements
void Statements()
{
    string word = readWord();
    if (word == "end")
        return;
    else
        Statement(word);

    Statements();
    return;
}

// read an individual statement
void Statement(string word)
{
    if (word == "print")
    {
        print_st();
    }
    else if (word.length() == 1 && isalpha(word[0]))
    {
        assign_st(word);
    }
    else
    {
        cerr << "Statement Error: invalid statement" << endl;
        exit(1);
    }
    return;
}

// process an assignment statement
void assign_st(string leftSide)
{
    string word = readWord();
    if (word.length() != 1 || word[0] != '=')
    {
        cerr << "assign_st Error: equal operator not found" << endl;
        exit(1);
    }

    string rightSide = "";
    rightSide += prog[indexx];
    if (isalpha(rightSide[0])) // right side is an id
    {
        word = readWord();
        if (word.length() != 1)
        {
            cerr << "assign_st Error: symbol length greater rthan 1" << endl;
            exit(1);
        }

        int leftPosition = findSymbolById(leftSide[0]);
        int rightPosition = findSymbolById(rightSide[0]);

        if (leftPosition == -1 || rightPosition == -1)
        {
            cerr << "assign_st Error: symbol not found" << endl;
            exit(1);
        }

        symbol_table[leftPosition].val = symbol_table[rightPosition].val;
    }
    else // right side is an expression
    {
        int value = Exp();
        int position = findSymbolById(leftSide[0]);

        if (position >= 0)
        {
            symbol_table[position].val = value;
        }
        else
        {
            cerr << "assign_st Error: symbol not found" << endl;
            exit(1);
        }
    }

    string semicolon = readWord();
    if (semicolon[0] != ';')
    {
        cerr << "assign_st Error: semicolon not found" << endl;
        exit(1);
    }

    return;
}

// print statement
void print_st()
{
    char id = prog[indexx];
    if (isalpha(id))
    {
        indexx++;
        int position = findSymbolById(id);
        if (position > -1)
        {
            cout << symbol_table[position].val << endl;
        }
        else
        {
            cerr << "print_st Error: symbol not found" << endl;
            exit(1);
        }
    }
    else
    {
        cout << Exp() << endl;
    }

    string word = readWord();
    if (word[0] != ';')
    {
        cerr << "print_st Error: no semicolon found" << endl;
        exit(1);
    }

    return;
}

int findSymbolById(char id)
{
    for (int i = 0; i < symbol_table.size(); i++)
    {
        if (symbol_table[i].id == id)
            return i;
    }
    return -1; // symbol not found
}

void printSymbolTable()
{
    cout << endl
         << "---SYMBOL TABLE---" << endl;
    cout << "i\t" << "id\t" << "type\t" << "value" << endl;
    for (int i = 0; i < symbol_table.size(); i++)
    {
        cout << i << "\t" << symbol_table[i].id << "\t";
        if (symbol_table[i].type == "int")
        {
            cout << "int\t";
        }
        else
        {
            cout << "double\t";
        }
        cout << symbol_table[i].val << endl;
    }
}

void Declarations()
{
    string word = readWord();
    if (word == "begin")
    {
        // cerr << "Declarations Error 1" << endl;
        // exit(1);
        return;
    }
    else if (word == "int" || word == "double")
    {
        Declaration(word);
    }
    else
    {
        cerr << "Declarations Error: Unexpected word" << endl;
        exit(1);
    }
    Declarations();
    return;
}

// Declaration stores data types into the symbol table.
// type is either 'int' or 'double'
void Declaration(string type)
{
    string id;

    while (true)
    {
        id = readWord();
        if (id.length() != 1 || !isalpha(id[0]))
        {
            cerr << "Declaration Error: id is not valid" << endl;
            exit(1);
        }

        symbol newSymbol;
        newSymbol.id = id[0];
        newSymbol.type = type;
        symbol_table.push_back(newSymbol);

        id = readWord();
        if (id == ",")
            continue;
        else
            break;
    }
    if (id != ";")
    {
        cerr << "Declaration Error: No semicolon found" << endl;
        exit(1);
    }
    return;
}

char readChar()
{
    char a = prog.at(indexx++); // get one char from program string
    while (a == ' ' && indexx < prog.length())
        a = prog.at(indexx++);

    return a;
}

// handles addition and subtraction
int Exp()
{
    return Exp2(Term());
}

// handles multiplication and division
int Term()
{
    return Term2(Power());
}

// helper function for expression
int Exp2(int inp)
{
    int result = inp;
    if (indexx < prog.length()) // if not the end of program string
    {
        char a = readChar();

        if (a == '+')
            result = Exp2(result + Term()); // handles T+T
        else if (a == '-')
            result = Exp2(result - Term()); // handles T-T
        else
            indexx--; // undo increment if not a valid operator
    }
    return result;
}

// helper function for term
int Term2(int inp)
{
    int result = inp;
    if (indexx < prog.length())
    {
        char a = readChar();

        if (a == '*')
            result = Term2(result * Power()); // handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Power()); // handles consecutive / operators
        else if (a == '+' || a == '-')        // if + or -, get back one position
            indexx--;
        else
            indexx--; // undo increment if not a valid operator
    }
    return result;
}

// handles exponents
int Power()
{
    return Power2(Fact());
}

// helper function for power
int Power2(int inp)
{
    int result = inp;
    if (indexx < prog.length())
    {
        char a = readChar();

        if (a == '^')
            result = pow(result, Power()); // handles result ^
        else
            indexx--; // invalid operator
    }
    return result;
}

int Fact()
{
    char a = prog[indexx]; // get one char from program string
    while (a == ' ' && indexx < prog.length())
    {
        indexx++;
        a = prog[indexx];
    }

    if (a == '(')
    {
        indexx++;
        int result = Exp(); // evaluate expression

        if (prog[indexx] != ')')
        {
            cerr << "parentheses don't match" << endl;
            exit(1);
        }
        indexx++;
        return result;
    }

    int num = 0;
    while (isdigit(prog[indexx]))
    {
        num = num * 10 + (prog[indexx] - '0');
        indexx++;
    }
    return num;
}