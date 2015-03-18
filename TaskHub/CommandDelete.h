#ifndef COMMANDDELETE_H_
#define COMMANDDELETE_H_

#include<iostream>
#include<string>
using namespace std;

class CommandDelete {
public:
	static string deleteMessage(string input);

private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif