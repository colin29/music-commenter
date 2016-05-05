#include <string>

class SongEntry{
	public:
	std::string title;
	std::string path;
	std::string comment;
};

enum Command {
	ADD = 3, DEL = 1, RN = 2, PRINT = 0, EXIT = 0, INVALID_COMMAND = -1, HELP = 0
};


Command parseCommand(vector<string>& params);


//printCommandList prints the availible commands and format to use them.
void printCommandList();

void printListOfSongEntries();
void printSongEntry(const SongEntry &songEntry);