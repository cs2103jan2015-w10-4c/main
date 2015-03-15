
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
#include "Storage.h"

using namespace std;

class UI {
public:
	enum COMMAND_TYPE {
		HELP, ADD_Textbody, UPDATE, DELETE_Textbody, SEARCH, DISPLAY_TextbodyS, MARK_DONE, UNDO, REDO, EXIT, INVALID
	};

private:
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_TERMINATION;
	static const string MESSAGE_ERROR;
	static COMMAND_TYPE determineCommandType(string commandTypeString, string TextbodyString);

	static string getFirstWord(string userCommand);
	static string removeFirstWord(string userCommand);
	static string getMessage(string TextbodyString);

	static string help();

public:
	static string executeUserCommand(string userCommand);
	static string displayWelcomeMessage();
	static string getUserCommand();

	static void showToUser(string text);
};
#endif
