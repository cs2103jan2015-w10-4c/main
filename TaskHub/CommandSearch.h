#ifndef COMMANDSEARCH_H_
#define COMMANDSEARCH_H_

#include<iostream>
#include<string>
using namespace std;

class CommandSearch {
public:
	static string searchMessage(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif