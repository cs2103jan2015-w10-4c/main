//@author A0115793Y
//************************************************
//				Class UI
//This class is to display user interface. 
//It will display all task, task on a specific day, search result, detail of a task.
//It will display system feedback(whether the command is successfully excecuded) to user.
//
//
//************************************************
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
#include <iomanip>
#include <Windows.h>
#include <iostream>
#include "LogicController.h"
#include "StorageController.h"
#include "CommandInterpreter.h"
#include "CommandDisplay.h"
#include "CommandSearch.h"
#include "CommandDetail.h"
#include "ShowDailyTask.h"
#include "Parser.h"

using namespace std;

class UI {

private:
	static const string MESSAGE_WELCOME;
	
public:
	static void programmeInitialising();
	static void displayWelcomeMessage();
	static string getUserCommand();
	static void showToUser(string userCommand);
	static void systemFeedback(string text);
	static void displayDay(vector<string> task, string heading);
	static void displayDetail(string task, string index);
};
#endif
