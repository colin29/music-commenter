
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




//returns -1 for invalid command
Command getParamCountForCommand(string command){
	for(char &c : command){
		c = toupper(c);
	}
	if(command == "ADD"){
		return Command::ADD;
	}else if(command == "DEL"){
		return Command::DEL;
	}else if(command == "RN"){
		return Command::RN;
	}else if(command == "PRINT"){
		return Command::PRINT;
	}
	else if (command == "ExIT") {
		return Command::EXIT;
	}
	else if (command == "HELP") {
		return Command::HELP;
	}else {
		return Command::INVALID_COMMAND;
	}
}

vector<SongEntry> songEntries;
int main(){


	bool end = false; //used by the EXIT command to exit the program.


	bool shownCommandList = false;

	while(!end){
		//Display the list of commands and await input from user
		if (!shownCommandList) {
			printCommandList();
			shownCommandList = true;
		}
		vector<string> params;
		Command command = parseCommand(params);

		if (command != Command::INVALID_COMMAND) {
			//do the command parsed
		}
	}


	return 0;
}


Command parseCommand(vector<string>& params) 
{
	params.clear();

	//extract the command token
	cin.clear();
	string command = "";
	cin >> command;

	char curParam[1000];
	int paramCounter = 0;


	bool doneParsingCommand = false;
	//extract parameters until a unqualified linebreak is reached (quotations can contain newlines)
	//each loop extracts a single parameter
	while (true) {
		paramCounter += 1;
		curParam[0] = '\0';

		//discard leading or excess white space characters
		while (cin.peek() == ' ') {
			cin.ignore();
		}

		char c = cin.peek();
		if (c == '\n') {
			break;
		}
		else if (c == '\"') { //extract parameter until reach a double quotation mark
			cin.ignore();
			cin.get(curParam, sizeof curParam / sizeof(*curParam), '\"'); //
			cin.ignore();
		}
		else { //regular space-seperated parameter.
			while (true) {
				char d = cin.get();
				if (d == '\n' || d == ' ') {
					if (d == '\n') {
						doneParsingCommand = true;
					}
					break; //done reading this parameter.
				}
			}

		}

		if (cin.fail()) {
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
	Command cCommand = getParamCountForCommand(command);
	int numOfParams = static_cast<int>(cCommand);
	if (numOfParams == -1) {
		cout << "Error: Invalid Command \"" << command << "\"" << endl;
		return Command::INVALID_COMMAND;
	}
	else if (params.size() != numOfParams) {
		cout << "Error: wrong number of parameters " << params.size() << ", expected: " << numOfParams << endl;
		return Command::INVALID_COMMAND;
	}

	cout << "Parsing command success " << "(" << command << ")" << endl;
	return cCommand;
}


void printCommandList(){
	cout << "Command List:" << endl;
	cout << "add <entry_title> <path> <description>" << endl;
	cout << "del <entry_title>" << endl;
	cout << "rn <entry_title> <new_entry_title>" << endl;
	cout << "print" << endl;
	cout << "exit" << endl;
	cout << "Type help to reshow command list" << endl;
	cout << "===============" << endl;
}

void printListOfSongEntries(){
	cout << "Listing all Song Entries:" << endl;
	for (SongEntry &se : songEntries) {
		printSongEntry(se);
	}
}

void printSongEntry(const SongEntry &se){
	cout << "Title: " << se.title << endl;
	cout << "Path: " << se.path << endl;
	cout << "Comment: " << se.comment << endl;
}

