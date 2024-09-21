// Interpreter for simplified infix expression with {+, -, *, /, ^ } operations;
// Keyboard input, single digit numbers only and no spaces are allowed;
// compile: $> g++ prog1.cpp
// run with: 2+3*4/2+3+4*2 or (3+2)*2^3

#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <cmath> 
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
        if (!isspace(ch) && ch != '\n')
            prog += ch;
        if (ch == '\n')
        {
            int result = Exp();
            cout << "result=" << result << endl;
        }
    }
    int result = Exp();
    cout << "result= " << result << endl;
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
        char a = prog.at(indexx++); // get one char from program string
        if (a == '^')
            result = pow(result, Power()); // handles result ^
        else
            indexx--; // invalid operator
    }
    return result;
}

// handles number and parentheses
int Fact()
{
    char a = prog.at(indexx++); // get one char from program string
    if (a == '(')
    {
        int result = Exp(); // evaluate expression
        if (prog.at(indexx++) != ')')
        {
            cerr << "parentheses don't match" << endl;
            exit(1);
        }
        return result;
    }
    else
    {
        return a - '0';
    }
}
