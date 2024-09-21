// Interpreter for simplified infix expression with {+, -, *, / } operations;
// Keyboard input, single digit numbers only and no spaces are allowed;
// compile: $> g++ prog1.cpp
// run with: 2+3*4/2+3+4*2

#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact();
string prog;    // string for reading 1-line input expression (program)
int indexx = 0; // global index for program string

int main(int argc, const char **argv)
{
    // Open file
    ifstream inputFile("input.txt");
    if (!inputFile)
    {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    // Read input from file
    char ch;
    while (inputFile.get(ch))
    {
        if (!isspace(ch))
            prog += ch;
    }

    int result = Exp();
    cout << "result= " << result << endl;
}

// handles addition and subtraciton
int Exp()
{
    cout << "Exp()" << endl;
    return Exp2(Term());
}

// handles multiplication and division
int Term()
{
    cout << "Term()" << endl;
    return Term2(Fact());
}

// helper funciton for expression
int Exp2(int inp)
{
    cout << "Exp2()" << endl;
    int result = inp;
    if (indexx < prog.length()) // if not the end of program string
    {
        char a = prog.at(indexx++); // get one chr from program string
        if (a == '+')
            result = Exp2(result + Term()); // handles T+T
        else if (a == '-')
            result = Exp2(result - Term()); // handles T-T
    }
    return result;
}

// helper funciton for term
int Term2(int inp)
{
    cout << "Term2()" << endl;
    int result = inp;
    if (indexx < prog.length())
    // if not the end of program string
    {
        char a = prog.at(indexx++); // get one chr from program string
        if (a == '*')
            result = Term2(result * Fact()); // handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Fact()); // handles consecutive / operators
        else if (a == '+' || a == '-')       // if + or -, get back one position
            indexx--;
    }
    return result;
}

// handles single digit numbers
int Fact()
{
    cout << "Fact()" << endl;
    char a = prog.at(indexx++); // get one chr from program string
    return a - '0';             // converts a char to a numeric number and return
}
