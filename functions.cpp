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
#include<stdlib.h>

#include"myfunctions.h"

using namespace std;

//EXPRESSION FUNCTIONS 

expression::expression(){} //ask odmaa what is the need of this

expression::expression(string Lside,string Rside,bool found,int evalCount,int linesread,map<string,string> *symbolTable,bool isE,float a):isEvaluated(isE),ans(a){
	bool token=false;
	stringstream sa(ios_base::app | ios_base::out);
	string str_answer="";
	for(int i=0;i<Rside.size();i++)
	{ 

		linesread++; //after valid only!!!!!!!!!!!!!!!!!!!!!!!
		if((64<int(Rside[i]) && int(Rside[i])<91) || (96<int(Rside[i]) && int(Rside[i])<123)) //if alphabet found in right side expression
			{ 																					//then we have a token
				token=true;
			}
	}

	if(token==true)	//if rside expression contains varibale,send rside expression to tokenize function
		{
			tokenize(Rside,Lside,found, symbolTable); //token in Rside so tokenize Rside //ASK
		}

	else 	//if rside expression only contains numbers and operators, immediatley evaluate (no alphabet/variables to tokenize)
		{
			ans=evaluate(Rside,found); //if does not contain token(any alphabet) then immediately evaluate
			sa<<ans;
			str_answer = sa.str();
			isEvaluated=true; //check point of
			evalCount++;
			symbolTable->insert({Lside,str_answer}); //add evaluated answer as value to symboltable, and left side as key
			for(auto x:*symbolTable){cout<<'{'<<x.first<<':'<<x.second<<'}'<<endl;}
		}
}


expression::~expression(){};

void expression::tokenize(string Rside,string Lside,bool found,map<string,string> *symbolTable){ //if variable found in rside expression, needs to be 
	int i=0;
	int tokenCount=-1; //count to account for multiple token in
	string Rsideback; //section of expression before token
	string Rsidefront; //section of expression after token
	string token="";
	stringstream ss(ios_base::app | ios_base::out);
	string str_answer="";
	//stack<string> skipped;
	vector<string> tokenVector; //vector that stores tokens
	while(i<=Rside.size()){ //Goes until end of expression
		if((64<int(Rside[i]) && int(Rside[i])<91) || (96<int(Rside[i]) && int(Rside[i])<123)){ //First char encountered
			string s(1,Rside[i]);//Converts char to string
			token=s; //Adds char to token name
			bool cont=true;
			int j=i+1;
			while(cont && found){
				if((64<int(Rside[j]) && int(Rside[j])<91) || (96<int(Rside[j]) && int(Rside[j])<123)){
					string s(1,Rside[j]);
					token=token+s;
					j++; //Move to the next char
				}

				else{cont=false;}	//Breaks loop when ascii values don't give char	 
			}

			i=j;//Skips over chars included in token
			i++;
			tokenVector.push_back(token);

			for(auto x:tokenVector){
				tokenCount++;
			}

			if(symbolTable->find(token)==symbolTable->end()){ //Checks if token is new
				for(auto x:(*symbolTable)){cout<<'{'<<x.first<<':'<<x.second<<'}'<<endl;}
					//skipped.push(Lside);
					//Lside="##";
				symbolTable->insert({Lside,"##"});
				isEvaluated=false;
				found=false;
				
			}
			else {//TOKEN FOUND IN DICTIONARY
				found=true;

				if(Rside.find(token[token.size()-1])==Rside.size()-1){
					Rsideback="";}
					else{
						Rsideback=Rside.substr(Rside.find(token[token.size()-1])+1,(Rside.size()-Rsidefront.size()-token.size()));
					}
				if(Rside.find(token[0])==Rside[0]){
					Rsidefront="";}
					else{
						Rsidefront=Rside.substr(0,Rside.find(token[0]));//Creates
					}
				string found_token=(*symbolTable)[token];
				if(found_token=="##"){found=false;}



				Rside=Rsidefront+found_token+Rsideback;//Goes and replaces the dicionary value with value dictionary key
				}
		}
		else {i++;} //Increments for next char 
		}		if(found){
				ans=evaluate(Rside,found); //after all tokens replaced(rside consists only of nums and operators), we send it to be evaluated
				ss<<ans;
				str_answer = ss.str();
				isEvaluated=true;
				symbolTable->insert({Lside,str_answer}); //Adding token 
				for(auto x:*symbolTable){cout<<'{'<<x.first<<':'<<x.second<<'}'<<endl;}}
	}


float expression::evaluate(string exp,bool found){
	while(found){
	string front="";
	string back=""; 
	for(int i=0; i<exp.size()-1; i++){

		
		if(isUnary(exp[i],exp[i+1]) ){ 
		//Changing unary to binary
		front=exp.substr(0,i);
		back=exp.substr(i+2,exp.size()-1);//Double check if limits of splice are correct

			//raise to the power of 2 "**" becomes "2^"
			if(exp[i]=='*'){ //edited from ** to * and * so watch out for

				exp[i]='2';
				exp[i+1]='^';
				//exp=front+'$'+back;
			}
			
			//up to here has to be replacing at those indices
		}
		
		if(i==0 && exp[i]=='-'){ //Checks for negative float at the front of exp -(-123-4)
			exp='0'+exp;
			i++;

		}
		
		else if(isOperator(exp[i]) && exp[i+1]=='-'){
			int k=0;
			int counter=0;
			string front="";
			string back1="";
			string back2="";
			front=exp.substr(0,i+1);
			k=(2+i);
			while(!isOperator(exp[k]) && exp[k]!=')' && exp[k]!='(' && exp[k]!=exp[exp.size()-1]){k++;counter++;}
	
	
			back1=exp.substr(i+2,counter);//Double check if limits of splice are correct

			if((k-2)==exp.size()-1){back2="";}
			else{
			back2=exp.substr(k,(exp.size()-front.size()-back1.size()));}
			exp=front+"(0-"+back1+')'+back2;
		
		}

		//for op then +
		else if(isOperator(exp[i]) && exp[i+1]=='+'){
			int k=0;
			int counter=0;
			string front="";
			string back="";

			if(exp[i]!='+' && exp[i+2]!='+'){
			front=exp.substr(0,i+1);
			back=exp.substr(i+2,exp.size()-1);//Double check if limits of splice are correct
	
			exp=front+back;}
			else if(exp[i]=='+'){ 
				int plus=0;
				for(int n=0;n<exp.size();n++){
					if(exp[n]=='+'){plus++;}
				}
				if((plus%2)!=0){ 
					//need to do for ++
					for(int k=0;k<plus-1;k++){
						int s=1;
						exp[i+s]='1';
						s=s+2;
					}

				}
				else{cout<<"Invalid input."<<endl;//valid=false;
		}
			}
		}
		else if(isOperator(exp[i]) && isOperator(exp[i+1])){
			cout<<"Invalid input."<<endl;
		}
		
		else if(!isalpha(exp[i]) && !isdigit(exp[i]) && !isOperator(exp[i])&& exp[i]!='(' && exp[i]!=')') //error checking: if file input not  
			{																	//alphabet, number nor operator, file input is invalid
				cout<<"Invalid input."<<endl;
			}
		else if(isOperator(exp[i])){
			if(i==exp.size()-1){
				cout<<"Invalid input."<<endl;
			}
		}
			
		else if(exp[i]=='+' && exp[i+1]=='-' || exp[i]=='-' && exp[i+1]=='+'){ //Checks for negative float at the front of exp (-3)
			exp[i]='-';
			exp[i+1]='0';
		}
		else if(exp[i]=='(' && exp[i+1]=='-'){ //Checks for negative float at the front of exp (-3)
			front=exp.substr(0,i);
			back=exp.substr(i+2,exp.size()-1);//Double check if limits of splice are correct
			exp=front+"(0-"+back;

		}
		if(exp[i]=='/' && exp[i+1]=='/'){ // "//" are all replaced out //front cant be empty hon //aslan not unary NEED TO DO
			exp[i]='#';
			exp[i+1]='0';

		}
		}

	exp=infix2postfix(exp,found); //Convert exp to postfix form 
	stack <float> myStack;				//1. Create a stack of type float to store the operands
	stringstream ss(ios_base::app | ios_base::out);
	string s="";
	string sign="";
	float eval=0;
	//2.	Scan the POSTFIX expression from left to right for every element
	for(int i=0; i<exp.size(); i++){
		if (exp[i]=='<'){
			int j=1;
			string num="";
			while(exp[i+j]!='>'){
				num=num+exp[i+j];
				j++;
			}
			i=i+j; 
			float fnum=std::stof(num);
			myStack.push(fnum);
		}
		else if(isOperator(exp[i])){
			//	b.	if the element is an operator pop 2 elements from the stack, apply the operator on it and push the result back to the stack
				if(exp[i]=='-'||exp[i]=='/'||exp[i]=='*'||exp[i]=='+'||exp[i]=='#'){ //Binary Operators
					float b=myStack.top();
					myStack.pop();
					float a=myStack.top();
					myStack.pop();
					float final;
					
					//need to make special case for a and b too enno they gotta be ints
					if(exp[i]=='/'){
						final=a/b;
					}
					else if (exp[i]=='#'){ //integer division when "//",Not sure about exactly what "//" does
						final=float(int(a/b)); //here casting
					}
					else if(exp[i]=='*'){
						final=a*b;
\
					}
					
					else if (exp[i]=='+'){
						final=a+b;

					}
					else if (exp[i]=='-'){
						final=a-b;

					}
					myStack.push(final);
			}

			else if(exp[i]=='%'||exp[i]=='^'){
				int specialcase_b=int(myStack.top());
				myStack.pop();
				int specialcase_a=int(myStack.top());
				myStack.pop();
				int specialcase_final;
				if(exp[i]=='%'){
						specialcase_final=specialcase_a%specialcase_b;
					}
				else if(exp[i]=='^'){
					specialcase_final=specialcase_a^specialcase_b;
				}
				myStack.push(float(specialcase_final));
			}
			
			}

		}
		//3. return the value from the top of the stack (i.e. the final answer)
		return myStack.top();
		while(!myStack.empty()){myStack.pop();} //empty stack evaluation of expression
	
}}
	//3. return the value from the top of the stack (i.e. the final answer)


string expression::infix2postfix(string infix,bool found){
	while(found){
	stack <char> mystack;
	string postfix="";
	// 1.	Push “(“onto Stack, and add “)” to the end of INFIX.
	mystack.push('(');
	infix=infix+')';
	// 2.	Scan INFIX from left to right and repeat Step 3 to 6 for each element of INFIX until the Stack is empty.
	for(int i=0;i<infix.size();i++){
			if(infix[i]=='('){ // 4.	If a left parenthesis is encountered, push it onto Stack.
				mystack.push(infix[i]);
			}
			//HON
				// 3.	If an operand is encountered, add it to POSTFIX.
				if(isdigit(infix[i])){	//if infix expression[i] is a digit, either...
					int j=0;
					string num="";
					while(isdigit(infix[i+j]) || infix[i+j]=='.'){
						if((infix[i+j])=='.'){	//a. if infix[i+j] is a decimal point, add it to num
							num+='.';
						}
						else{num+=infix[i+j];}	//b. else infix[i+j] is a digit and is added to num	
						j++;
					}
					i=i+j-1;
					postfix=postfix+"<"+num+">";
				}
						//Skips second digit 
				
			//LA HON
			else if(isOperator(infix[i])) {	// 5.	If an operator is encountered, then: 
				while(isOperator(mystack.top()) and isleq(infix[i],mystack.top())){
					// 	a.	Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack) which has the same precedence as or higher precedence than operator.
					postfix+=mystack.top();
					mystack.pop();
				}
				mystack.push(infix[i]);	// 	b.	Add operator to Stack.
			}

			else if(infix[i]==')'){// 6.	If a right parenthesis is encountered, then:
				// 	a.	Repeatedly pop from Stack and add to POSTFIX each operator (on the top of Stack) until a left parenthesis is encountered.
				while(mystack.top()!='('){
					postfix+=mystack.top();
					mystack.pop();
				}
				// 	b.	Remove the left Parenthesis.
				mystack.pop();
			}
		
				//--------------------------------NEW!!!!!!!!!!!!!
				//.6.	If a right parenthesis is encountered, then: 
				
}
	return postfix;
	while(!mystack.empty()){mystack.pop();}
}}
void expression::print(){
	cout<<"ans:"<<ans<<endl;
	//cout<<"this is left side: "<<Lside<<"="<<ans<<endl;
}
bool expression::isOperator(char ch)
	{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^'|| ch=='#' || ch=='%')
		return true;
	else
		return false;
	}
bool expression::isUnary(char ch1, char ch2){
	if(isOperator(ch1) && ch1==ch2 && ch1!='(' && ch1!='^'){
		return true;
	}
	else{
		return false;
	}
}

bool expression::isleq(char opA, char opB)
{
	return (convertOpToInt(opA)<=convertOpToInt(opB));
}
int expression::convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/' || ch=='%'||ch=='@') return 2; //*, /, //, %
    if (ch=='^') return 3;
    //if (ch=='@' || ch=='~'||ch=='$'||ch=='[') return 4; //Unary operators have higher precedence 
    return 0;
}
//----------------------------------------------------------------------------------------------------------





