// Interpreter for simplified infix expression with {+, -, *, /, ^ } operations;
// Keyboard input, single digit numbers only and no spaces are allowed;
// compile: $> g++ prog1.cpp
// run with: 2+3*4/2+3+4*2 or (3+2)*2^3

#include <cstdlib> // for atoi()
#include <iostream>
#include <fstream>
#include <cmath> // for pow()
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Power(), Power2(int);
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

// handles addition and subtraction
int Exp()
{
    cout << "Exp()" << endl;
    return Exp2(Term());
}

// handles multiplication and division
int Term()
{
    cout << "Term()" << endl;
    return Term2(Power());
}

// helper function for expression
int Exp2(int inp)
{
    int result = inp;
    if (indexx < prog.length()) // if not the end of program string
    {
        char a = prog.at(indexx++); // get one char from program string
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
        char a = prog.at(indexx++); // get one char from program string
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

// handles exponentiation (right-associative)
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
        char a = prog.at(indexx++); // get one char from program string
        if (a == '^')
            result = pow(result, Power()); // right-associative exponentiation
        else
            indexx--; // undo increment if not a valid operator
    }
    return result;
}

// handles single digit numbers and parentheses
int Fact()
{
    char a = prog.at(indexx++); // get one char from program string
    if (a == '(')
    {
        int result = Exp();           // evaluate the expression inside parentheses
        if (prog.at(indexx++) != ')') // expect closing parenthesis
        {
            cerr << "Error: Mismatched parentheses!" << endl;
            exit(1);
        }
        return result;
    }
    else
    {
        return a - '0'; // converts a char to a numeric number and return
    }
}
