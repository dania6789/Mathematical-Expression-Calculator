#ifndef FUNCTION_H
#define FUNCTION_H
//function declarations
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<cmath>
#include<stack>
#include<map>
#include<vector>
#include<sstream>
#include<string.h>
#include<algorithm>
#include<cstdio>

using namespace std;


//EXPRESSION CLASS


class expression{
private:
	string Lside;
	string Rside;
	bool isEvaluated;
	float ans;
	
public:
	expression();
	expression(string Lside,string Rside,bool found,int evalCount,int linesread,map<string,string> *symbolTable,bool isE=false,float a=0);
	~expression();
	void tokenize(string Rside, string Lside,bool found,map<string,string> *symbolTable);
	string infix2postfix(string infix,bool found);
	float evaluate(string exp,bool found);
	void print(); 
	bool isOperator(char ch);
	bool isUnary(char ch1, char ch2);
	bool isleq(char opA, char opB);

	int convertOpToInt (char ch);
	string operator+(string);

};

#endif