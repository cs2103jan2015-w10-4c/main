#ifndef COMMANDSEARCH_H_
#define COMMANDSEARCH_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CommandSearch {
public:
	CommandSearch ();
	~CommandSearch ();
	static string searchMessage(string input);
	static vector <string> messageDisplayed;

private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_CANNOT_FIND;
	static const string MESSAGE_EMPTY_FILE;
	static const string MESSAGE_IS_SHOWN;
};


#endif