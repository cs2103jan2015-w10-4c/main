#ifndef COMMANDINTERPRETER_H_
#define COMMANDINTERPRETER_H_

#include <iostream>
#include <string>
#include <algorithm>
#include "Logic.h"
using namespace std;

class CommandInterpreter {
	public:
	enum COMMAND_TYPE {
		HELP, ADD_Task, UPDATE, DELETE_Task, SEARCH, DISPLAY_TaskS, MARK_DONE, UNCONPLETE, UNDO, REDO, SHOW, EXIT, INVALID
	};
private:
	static const string MESSAGE_ERROR;
	static const string MESSAGE_TERMINATION;
	static string getFirstWord(string userCommand);
	static string removeFirstWord(string userCommand);
	static string getMessage(string TaskString);
	static COMMAND_TYPE determineCommandType(string commandTypeString, string TaskString);

public:
	static string executeUserCommand(string userCommand);


};

#endif