#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
#include<stack>
#include<map>
#include<vector>
#include<string.h>
#include<algorithm>
#include<stdlib.h>

#include"myfunctions.h"

using namespace std;


int main(int argc, char* const argv[]){ //Takes input file name from main and output filename from main
	ifstream inFile;
	ofstream outFile;
	string line;
	string filename;
	string outfile;
	vector<expression> finallist; //ask odmaa
	bool display=false; //false if -o provided(prints in outfile.txt),true if -o not provided (prints in terminal)
	int commandlineArgs=0;
	map<string,string> symbolTable; //map to store keys(variable names) and respective values
	int counter=0;
	int linesread=0;
	int evalCount=0; //tracking number of lines evaluated to compare to number of lines read, when equal, all input has been processed
	bool found=true;
	bool cont=true;
	int loop=0;

	for(int i=0;i<argc;i++) //processing command line args
		{
			if (strcmp(argv[i], "-i") == 0) 
				{filename=argv[i+1]; commandlineArgs++;} //saving filename as arguement that follows "-i" string
				
			else if (strcmp(argv[i],"-o") == 0)
				{outfile=atoi(argv[i+1]); commandlineArgs++;} //saving outfile as arguement that follows "-o" string, outfile is where the evaluated expressions "results" are stored
				
			else if(strcmp(argv[i], "-i") == -1)
				{cout<<"Please make sure to enter an input file"<<endl; exit(1);} //will crash anyways so askings

			else if(strcmp(argv[i],"-o") == -1)
				{display=true;}
		}


		inFile.open(filename);
		if(inFile.is_open()){
			for(auto x:symbolTable){
				if(x.second=="##")
					{cont=true;} 
				else
					{cont=false;}}	

			while(cont && loop!=1){ //MAIN LOOP
				getline(inFile,line);
				if(line=="") continue; //if line = blank line, skip it
				line.erase(remove(line.begin(), line.end(), ' '), line.end()); //ignore whitespace when reading lines in txt file
				cout<<"cont: "<<cont<<endl;
				cout<<endl<<endl<<"**********************NEW LINE*******************"<<endl<<"text file line: "<<line<<endl;
				string Lside=line.substr(0,line.find('=')); //save section before "=" as the left side
				cout<<"lside: "<<Lside<<endl;
				string Rside=line.substr(line.find('=')+1,((line.size()-1)-(Lside.size()+1))); //save section after "=" and before ";" as right side
				cout<<"rside: "<<Rside<<endl;
				expression newexp=expression(Lside,Rside,found,evalCount,linesread,&symbolTable); //create class expression object "newexp" and pass lside,rside and symbol table to constructor
				finallist.push_back(newexp);//Adds final objects to the finallist to print //we are saving putput in outfile, we can change later and test in in print for now to see changes 
				cout<<"size of final list: "<<finallist.size()<<endl;
				if(inFile.eof()!=0){ cout<<"entered end of file"<<endl;
					for(auto x:symbolTable){
						if(x.second=="##"){
							string key=symbolTable["##"];
							cout<<"key: "<<key<<endl;
							string skipped_Rside=key.substr(2,key.size()-2);
							cout<<"skipped rside: "<<skipped_Rside<<endl;
							cout<<"lside w respect to ##: "<<Rside<<endl;
							inFile.seekg(0, ios::beg);
							getline(inFile,line);
							if(line=="") continue; //if line = blank line, skip it
							line.erase(remove(line.begin(), line.end(), ' '), line.end()); //ignore whitespace when reading lines in txt file
							cout<<"cont: "<<cont<<endl;
							cout<<endl<<endl<<"**********************NEW LINE*******************"<<endl<<"text file line: "<<line<<endl;
							string Lside=line.substr(0,line.find('=')); //save section before "=" as the left side
							cout<<"lside:hay??? "<<Lside<<endl;
							string Rside=line.substr(line.find('=')+1,((line.size()-1)-(Lside.size()+1))); //save section after "=" and before ";" as right side
							cout<<"rside:hay? "<<Rside<<endl;
							if(Rside==skipped_Rside){
							loop++;
							newexp=expression(Lside,Rside,found,evalCount,linesread,&symbolTable); //create class expression object "newexp" and pass lside,rside and symbol table to constructor
							finallist.push_back(newexp);//Adds final objects to the finallist to print //we are saving putput in outfile, we can change later and test in in print for now to see changes 
							cout<<"size of final list: "<<finallist.size()<<endl;
							expression newexp=expression(Lside,Rside,found,evalCount,linesread,&symbolTable);} //create class expression object "newexp" and pass lside,rside and symbol table to constructor
							
							//else{continue;}
							
					
						}
					}

				}
				

	}

					if(display==false)
						{
							cout<<"entered display=false ya3ni elmafrood is printing in outfile"<<endl;
							outFile.open("outfile.txt"); 
							for(auto x:symbolTable)
								{outFile<<x.first<<'='<<x.second<<endl;}
							outFile.close();
							exit(1);
						}
					else
						{
							for(int i=0; i<finallist.size(); i++){
							finallist[i].print();	}
							cout<<endl<<"All input evaluated"<<endl;}
							
						exit(EXIT_FAILURE); //program terminates
}
	return 0;
	}