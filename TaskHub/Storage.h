#ifndef STORAGE_H_
#define STORAGE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include "Logic.h"

using namespace std;

class storage{
private:
	static vector<string> Task;
	static const string fileName;

public:
	static void programmeInitialising();
	static void programmeTerminating();
	static vector<string> returnTask();
};

#endif
