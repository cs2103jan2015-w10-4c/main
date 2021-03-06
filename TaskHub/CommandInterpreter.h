//@author A0115365J

//
//************************************************
//				Class CommandInterpreter
//this class is used when user key in something
//it will determine the command type for the message and pass it to LogicController for further implementation
//
//the following commands are supported:
//HELP, ADD_TASK, CLEAR, UPDATE, RECURRING, DELETE_TASK, SEARCH, CHECK, SORT, DISPLAY_TASK, 
//		DETAIL, MARK_DONE, UNCONPLETE, UNDO, REDO, SHOW, EXIT, INVALID
//
//************************************************

#ifndef COMMANDINTERPRETER_H_
#define COMMANDINTERPRETER_H_

#include <iostream>
#include <string>
#include <algorithm>
#include "LogicController.h"
using namespace std;

class CommandInterpreter {
	public:
		CommandInterpreter ();
		~CommandInterpreter ();
	enum COMMAND_TYPE {
		HELP, ADD_TASK, CLEAR, UPDATE, RECURRING, DELETE_TASK, SEARCH, CHECK, SORT, DISPLAY_TASK, 
		DETAIL, MARK_DONE, UNCONPLETE, UNDO, REDO, SHOW, EXIT, INVALID
	};
	static string executeUserCommand(string userCommand);
private:
	
	static string getFirstWord(string userCommand);
	static string removeFirstWord(string userCommand);
	static string getMessage(string TaskString);
	static COMMAND_TYPE determineCommandType(string commandTypeString, string TaskString);
	
	static const string MESSAGE_ERROR;
	static const string MESSAGE_TERMINATION;
	static const string COMMAND_ADD;
	static const string COMMAND_DELETE;
	static const string COMMAND_UPDATE;
	static const string COMMAND_CLEAR;
	static const string COMMAND_SHOW;
	static const string COMMAND_SEARCH;
	static const string COMMAND_SORT;
	static const string COMMAND_REDO;
	static const string COMMAND_UNDO;
	static const string COMMAND_RECURRING;
	static const string COMMAND_UNCOMPLETE;
	static const string COMMAND_CLASH;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_DONE;
	static const string COMMAND_HELP;
	static const string COMMAND_EXIT;
	static const string COMMAND_DETAIL;

};

#endif