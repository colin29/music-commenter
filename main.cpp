
#include <iostream>
#include <vector>

#include "main.h"

using std::string;
using std::vector;
using std::cin;
using std::cout;


vector<SongEntry> songEntries;

int main(){


	int input;
	bool end = false;
	while(!end){

		printCommandList();

		cin >> input;
		switch(input){
			case 1:

			case 2:

			case 3:

			case 0:
				end = true;
				break;
			default:
				break;
		}
	}


	return 0;
}