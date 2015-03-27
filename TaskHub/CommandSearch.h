#ifndef COMMANDSEARCH_H_
#define COMMANDSEARCH_H_

#include<iostream>
#include<string>
using namespace std;

class CommandSearch {
public:
	static string searchMessage(string input);
	static string printVector(vector<string> output);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_CANNOT_FIND;
	static const string MESSAGE_EMPTY_FILE;
};


#endif