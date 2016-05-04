#include <string>

class SongEntry{
	public:
	std::string title;
	std::string comment;
};

//printCommandList prints the availible commands and format to use them.
void printCommandList();

void printListOfSongEntries();
void printSongEntry(SongEntry songEntry);