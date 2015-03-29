#ifndef CLEARALL_H_
#define CLEARALL_H_

#include <iostream>
#include <string>
#include "Logic.h"
using namespace std;

class CommandClear {

public:
	static string clearTask(string input);
private:
	static const string MESSAGE_CLEAR_ALL;
	static const string MESSAGE_CLEAR_FROM_TO;
	static const string MESSAGE_CLEAR_ERROR;
	static const string MESSAGE_CLEAR_DONE;
	static const string MESSAGE_CLEAR_UNCOMPLETED;
};


#endif