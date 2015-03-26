#ifndef COMMANDMARKUNCOMPLETE_H_
#define COMMANDMARKUNCOMPLETE_H_

#include<iostream>
#include<string>
using namespace std;

class markingMessageUncomplete {
public:
	static string markMessageUncompleted(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_MARK_UNCOMPLETE;
	static const string MESSAGE_INVALID_INDEX;
};


#endif