//@author A0115365J
//
//************************************************
//				Class CommandAdd
//this class is to add new messages into the vector after constructing the messages in Parser
//this class will also check whether the new messages with existing ones by calling CommandClash function. If clashes occur
//nothing will be added.
//
//
//
//
//************************************************


#ifndef COMMANDADD_H_
#define COMMANDADD_H_

#include<iostream>
#include<string>
using namespace std;

class CommandAdd {
public:
	CommandAdd ();
	~CommandAdd ();
	static string addMessage(string input);
	static string addOperation(string input);
	static const string MESSAGE_INDICATING_EMPTY;
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_CLASH;
	static const string MESSAGE_INVALID_INPUT;
};

#endif