//@author A0115365J
//
//************************************************
//				Class CommandDelete
//this class is used when the delete command is called
//it can delete tasks with valid index
//
//
//************************************************


#ifndef COMMANDDELETE_H_
#define COMMANDDELETE_H_

#include<iostream>
#include<string>
using namespace std;

class CommandDelete {
public:
	static string deleteMessage(string input);
	CommandDelete ();
	~CommandDelete ();

private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_DELETED;
	static const string MESSAGE_INVALID_INDEX;
};


#endif