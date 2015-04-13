//@author A0115365J

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