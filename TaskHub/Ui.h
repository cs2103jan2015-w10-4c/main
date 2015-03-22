
#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <sstream>
#include <time.h>
#include "Logic.h"
#include "StorageController.h"

using namespace std;

class UI {
public:
	enum COMMAND_TYPE {
		HELP, ADD_Task, UPDATE, DELETE_Task, SEARCH, DISPLAY_TaskS, MARK_DONE, UNDO, REDO, EXIT, INVALID
	};

private:
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_TERMINATION;
	static const string MESSAGE_ERROR;
	static COMMAND_TYPE determineCommandType(string commandTypeString, string TaskString);

	static string getFirstWord(string userCommand);
	static string removeFirstWord(string userCommand);
	static string getMessage(string TaskString);

	static string help();

public:
	static string executeUserCommand(string userCommand);
	static string displayWelcomeMessage();
	static string getUserCommand();

	static void showToUser(string text);
};
#endif
