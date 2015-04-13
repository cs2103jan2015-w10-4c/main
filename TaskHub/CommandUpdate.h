//@author A0115365J

//
//************************************************
//				Class Update
//this class is used when the update command is called
//it will update the tasks, can be only task name, staring time, ending time, venue or all of them
//
//************************************************

#ifndef COMMANDUPDATE_H_
#define COMMANDUPDATE_H_

#include<iostream>
#include<string>
using namespace std;

class CommandUpdate {
public:
	CommandUpdate ();
	~CommandUpdate ();
	static string updateMessage(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_INVALID_INDEX;
	static const string MESSAGE_UPDATED;
};

#endif