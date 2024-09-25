/////////////////
// key code for Prog2.
// 
// $> g++ p2-key-for-students.cpp -o p2
// $> ./p2  p2-data
/////////////////

#include <cstdlib> //for atoi()
#include <iostream>
#include <fstream>
#include <math.h> //for pow(..)
using namespace std;

int Exp(), Term(), Exp2(int), Term2(int), Fact(), Fact2(int), Num();
ifstream fin;
string prog, s1; //prog for reading the entire input program (expression) from file
int indexx = 0;  //global index for program string

int main()
{ 
  // string path1 = "input3.txt";
  // fin.open(path1.c_str()); //open data file  
  // getline(fin, s1);   //read one line  
  // while (!fin.eof())  
  // { prog += s1;	     
  //   getline(fin, s1); //read next line
  // }  
  // cout << "prog: " << prog << endl;
  // cout << "s1: " << s1 << endl;
  prog = "(2^3)^+2^3^2";
  cout<<"result= "<<Exp()<<endl;
  fin.close();
}

int Exp()
{ return Exp2(Term()); 
}

int Term()
{ return Term2(Fact()); 
}

int Exp2(int inp)
{   
  int result = inp;
  if (indexx < prog.length()) //if not the end of program string
  { char a = prog.at(indexx++); //get one chr from program string
    while (a==' ' && (indexx < prog.length())) //if space, skip and read until a char
      a = prog.at(indexx++);
    if (a == '+')
      result = Exp2(result + Term());  //handles T+T, where T represents consecutive * or /
    else if (a == '-')                 //analogous for - operation
      result = Exp2(result - Term());
  }
  return result;
}

int Term2(int inp)
{   
  int result = inp;
  if (indexx < prog.length())   //if not the end of program string
  { char a = prog.at(indexx++); //get one chr from program string
    while (a==' ' && (indexx < prog.length())) //if space, skip and read until a char
      a = prog.at(indexx++);
    if (a == '*')
      result = Term2(result * Fact()); //handles consecutive * operators
    else if (a == '/')
      result = Term2(result / Fact()); //handles consecutive / operators
    else if (a == '+' || a == '-' || a == ')') //if + or -, get back one position
      indexx--;
  }
  return result;
}

int Fact()
{ return Fact2(Num());
}

int Fact2(int inp)
{ 
  int result = inp;
  if (indexx < prog.length())   //if not the end of program string
  { char a = prog.at(indexx++); //get one chr from program string
    while (a==' ' && (indexx < prog.length())) //if space, skip and read until a char
      a = prog.at(indexx++);
    if (a == '^')
      result = Fact2(pow(result, Fact()));
    else //this includes ')'
      indexx--; 
  }
  return result;
}

int Num()
{ 
  if (indexx < prog.length())
  { char a = prog.at(indexx++);
    while (a==' ' && (indexx < prog.length())) //if space, skip and read until a char
      a = prog.at(indexx++);
    if (a == '(')
      return Exp();
    return a - '0';  //converts a char to a numeric number and return
  }//if
}
