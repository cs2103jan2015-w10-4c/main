#ifndef COMMANDAUTOSORT_H_
#define COMMANDAUTOSORT_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "LogicController.h"
#include "Parser.h"
using namespace std;

class CommandAutoSort {

private:
	static const string STATUS_DONE;
	static const string STATUS_UNCOMPLETED;
	static const string STATUS_FLOATING;
	static const string MESSAGE_SORT_SUCCESSFUL;
	static const char NULL_TERMINATION_CHARACTER;

public:
	CommandAutoSort ();
	~CommandAutoSort ();
	static void sortTask(std::vector<Task> storage);
	static string autoSort ();
	static bool compareCriteria(Task first, Task second);

};


#endif