
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

		if (command == Command::ADD) {
			SongEntry n;
			n.title = params[0];
			n.path = params[1];
			n.comment = params[2];

			bool entryAlreadyExists = false;
			for(SongEntry &se : songEntries) {
				if(se.title == n.title) {
					entryAlreadyExists = true;
				}
			}
			if(!entryAlreadyExists) {
				songEntries.push_back(n);
			} else {
				cout << "Entry \"" << n.title << "\" already exists." << endl;
			}

		}else if(command == Command::DEL){
			string title = params[0];
			int erasedCount = 0;
			for(std::vector<SongEntry>::iterator it = songEntries.begin(); it != songEntries.end(); ++it){
				if(it->title == title) {
					it = songEntries.erase(it);
					erasedCount += 1;
				}
			}
			if(erasedCount == 0) {
				cout << "No entry with name \"" << title << "\" found." << endl;
			} else if(erasedCount > 1) {
				cout << "State Error: more than one entry with name \"" << title << "\" was found. (All were deleted, but there should not be multiples.)" << endl;
			} else if(erasedCount == 1) {
				cout << "Entry\"" << title << "\" succesfully erased." << endl;
			}

		}else if(command == Command::RN){
			string title = params[0];
			string newTitle = params[1];
			for(SongEntry &se : songEntries) {
				if(se.title == title) {
					se.title = newTitle;
				}
			}

		}else if(command == Command::PRINT){
			printListOfSongEntries();
		}else if(command == Command::EXIT){
			exit(0);
		}else if(command == Command::HELP){
			printCommandList();
		}else if(command == Command::INVALID_COMMAND){
			cout << "Error: Invalid Command" << endl;
		} else {
			cout << "Error: Unsupported Command" << endl;
		}

		if (command != Command::INVALID_COMMAND) {
			continue;
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
			int i = 0;
			while (true) {
				char d = cin.get();
				if (d == '\n' || d == ' ') {
					if (d == '\n') {
						doneParsingCommand = true;
					}
					curParam[i] = '\0';
					break; //done reading this parameter.
				} else {
					//add the character to the string.
					curParam[i] = d;
					i += 1;
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
	cout << "add <entry_title> <path> <description>" << endl; /* will fail if there is already a entry with the same title*/
	cout << "del <entry_title>" << endl;
	cout << "rn <entry_title> <new_entry_title>" << endl;
	cout << "print" << endl;
	cout << "exit" << endl;
	cout << "Type help to reshow command list" << endl;
	cout << "===============" << endl;
}

void printListOfSongEntries(){
	cout << "Listing all Song Entries:" << endl;
	cout << "---------------" << endl;
	for (SongEntry &se : songEntries) {
		printSongEntry(se);
		cout << "---------------" << endl;
	}
}

void printSongEntry(const SongEntry &se){
	cout << "Title: " << se.title << endl;
	cout << "Path: " << se.path << endl;
	cout << "Comment: " << se.comment << endl;
}

