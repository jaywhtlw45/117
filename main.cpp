//// Interpreter for simplified infix expression with {+, -, *, / } operations;
//// Keyboard input, single digit numbers only and no spaces are allowed;
//// compile: $> g++ prog1.cpp
//// run with: 2+3*4/2+3+4*2
#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>  //to read from input file

using namespace std;
int Exp(), Term(), Exp2(int), Term2(int), Fact();
string prog; //string for reading 1-line input expression (program)
int indexx = 0; //global index for program string
int main(int argc, const char **argv)
{
    ifstream ins ("input.txt");
    cout<<">";
    char x;
    while(ins.get(x))
    {
        if(isspace(x)) {continue;}  //if it encounters a space it will skip it
        prog += x;
    }
//cin>>prog;
        cout<<"result= "<<Exp()<<endl;

}
//Exp
int Exp()
{
    cout << "Exp() called" << endl;
    return Exp2(Term());
}
int Term()
{
    cout << "Term() called" << endl;
    return Term2(Fact());
}
int Exp2(int inp)
{
    cout << "Exp2() called" << endl;
    int result = inp;
    if (indexx < prog.length()) //if not the end of program string
    {
        char a = prog.at(indexx++); //get one chr from program string
        if (a == '+')
            result = Exp2(result + Term()); //handles T+T
        else if (a == '-')
            result = Exp2(result - Term()); //handles T-T
    }
    return result;
}
int Term2(int inp)
{
    cout << "Term2 called" << endl;
    int result = inp;
    if (indexx < prog.length()) //if not the end of program string
    {
        char a = prog.at(indexx++); //get one chr from program string
        if (a == '*')
            result = Term2(result * Fact()); //handles consecutive * operators
        else if (a == '/')
            result = Term2(result / Fact()); //handles consecutive / operators
        else if (a == '+' || a == '-') //if + or -, get back one position
            indexx--;
    }
    return result;
}
int Fact()
{
    cout << "Fact() called" << endl;
    char a = prog.at(indexx++); //get one chr from program string
    return atoi(&a); //converts a char to a numeric number and return
}
