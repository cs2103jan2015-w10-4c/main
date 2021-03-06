//@author A0115365J

//
//************************************************
//				Class CommandClear
//this class is used when the clear command is called
//it can clear all tasks, clear tasks with adjacent index, clear all uncompleted tasks, and all done tasks
//
//
//************************************************


#ifndef CLEARALL_H_
#define CLEARALL_H_

#include <iostream>
#include <string>
#include <algorithm>
#include "LogicController.h"
using namespace std;

class CommandClear {

public:
	CommandClear ();
	~CommandClear ();
	static string clearTask(string input);
private:
	static const string MESSAGE_CLEAR_ALL;
	static const string MESSAGE_CLEAR_FROM_TO;
	static const string MESSAGE_CLEAR_ERROR;
	static const string MESSAGE_CLEAR_DONE;
	static const string MESSAGE_CLEAR_UNCOMPLETED;
	static const string MESSAGE_CLEAR_COMMAND;
	static const string MESSAGE_ALL;
	static const string MESSAGE_CLEAR;
	static const string MESSAGE_DONE;
	static const string MESSAGE_UNCOMPLETE;
};


#endif