#ifndef COMMANDAUTOSORT_H_
#define COMMANDAUTOSORT_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Logic.h"
#include "Parser.h"
using namespace std;

class CommandAutoSort {

private:

public:
	static CommandAutoSort& getInstance() {
		static CommandAutoSort instance;
		return instance;
	}

	static void sortTask(std::vector<Task> storage);
	static void autoSort ();


};


#endif