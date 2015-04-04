
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
#include "CommandInterpreter.h"
#include "ShowDailyTask.h"

using namespace std;

class UI {

private:
	static const string MESSAGE_WELCOME;

public:
	static string displayWelcomeMessage();
	static string getUserCommand();
	static void showToUser(string userCommand, string text);
};
#endif
