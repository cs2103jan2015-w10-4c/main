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
