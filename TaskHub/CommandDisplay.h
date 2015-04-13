//@author A0115365J

//
//************************************************
//				Class CommandDisplay
//this class is used when the clear command is called
//it can display all tasks, display all uncompleted tasks only, and all done tasks only, all timed tasks only, all deadline tasks only
//and all floating tasks only
//
//************************************************

#ifndef COMMANDDISPLAY_H_
#define COMMANDDISPLAY_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CommandDisplay {
public:
	CommandDisplay ();
	~CommandDisplay();
	static string display(string message);
	static vector<string> messageDisplayed;
private:
	static const string MESSAGE_ALL;
	static const string MESSAGE_DISPLAY_WORD;
	static const string MESSAGE_DISPLAYED;
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_EMPTY_FILE;
	static const string MESSAGE_INVALID_COMMAND;
	static const string STATUS_UNCOMPLETE;
	static const string STATUS_DONE;
	static const string TASK_TYPE_TIMED;
	static const string TASK_TYPE_DEADLINE;
	static const string TASK_TYPE_FLOATING;
	static const string DOT;

	
};


#endif
