#ifndef COMMANDADD_H_
#define COMMANDADD_H_

#include<iostream>
#include<string>
using namespace std;

class CommandAdd {
public:
	static string addMessage(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_ADDED;
};

#endif