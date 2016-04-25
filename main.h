#include <string>

class SongEntry{
	public:
	std::string title;
	std::string comment;
};


void printCommandList();

void printListOfSongEntries();
void printSongEntry(SongEntry songEntry);