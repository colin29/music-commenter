
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

#include "main.h"

using std::string;
using std::vector;
using std::cin; 
using std::cout;
using std::endl;


enum ParamCount{
	ADD = 3, DEL = 1, RN = 2, PRINT = 0, EXIT = 0, INVALID_COMMAND = -1,
};


//returns -1 for invalid command
ParamCount getParamCountForCommand(string command){
	for(char &c : command){
		c = toupper(c);
	}
	if(command == "ADD"){
		return ParamCount::ADD;
	}else if(command == "DEL"){
		return ParamCount::DEL;
	}else if(command == "DEL"){
		return ParamCount::RN;
	}else if(command == "DEL"){
		return ParamCount::PRINT;
	}else if(command == "DEL"){
		return ParamCount::EXIT;
	}else{
		return ParamCount::INVALID_COMMAND;
	}
}

vector<SongEntry> songEntries;
int main(){


	string command;
	bool end = false; //used by the EXIT command to exit the program.

	//Display the list of commands and await input from user
	while(!end){

		printCommandList();

		
		
		//extract the command token
		cin.clear();
		command = "";
		cin >> command; 
		cout << "Recieved command: '"<< command << "'" << endl;
		

		char curParam[1000];
		vector<string> params;
		int paramCounter = 0;


		
		bool doneParsingCommand = false;

		//extract parameters until a unqualified linebreak is reached (quotations can contain newlines)
		while(true){ 
			paramCounter +=1;
			curParam[0] = '\0';

			//discard leading or excess white space characters
			while(cin.peek() == ' '){ 
				cin.ignore();
			} 
			
			char c = cin.peek();
			if(c == '\n'){ 	
				break;
			}else if(c == '\"'){ //extract parameter until reach a double quotation mark
				cin.ignore();
				cin.get(curParam, sizeof curParam/sizeof(*curParam), '\"'); //
				cin.ignore();
			}else{ //regular space-seperated parameter.
				while(true){
					char d = cin.get();
					if (d == '\n' || d == ' ') {
						if (d == '\n') {
							doneParsingCommand = true;
						}
						break; //done reading this parameter.
					}
				}

			}

			if(cin.fail()){
				cout << "Error: Parameter " << paramCounter << " is too long (mostly likely)" << endl;
				cin.clear();
				break;
			}

			string sParam = curParam;
			params.push_back(sParam);

			if (doneParsingCommand) {
				break;
			}

			
		}

		//validate command and number of parameters
		int numOfParams = static_cast<int>(getParamCountForCommand(command));
		if(numOfParams == -1){
			cout << "Error: Invalid Command \"" << command << "\"" << endl;
		}else if(params.size() != numOfParams){
			cout << "Error: wrong number of parameters " << params.size() << ", expected: " << numOfParams  << endl;
		}

		cout << "Parsing command success" << endl;
		//TODO: actually do the command.


	}


	return 0;
}




void printCommandList(){

}

void printListOfSongEntries(){

}

void printSongEntry(SongEntry songEntry){

}

