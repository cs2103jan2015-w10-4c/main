//@author A0115365J

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