#ifndef STORAGECONTROLLER_H_
#define STORAGECONTROLLER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include "Logic.h"

using namespace std;

class StorageController {
private:
	static vector<string> Task;
	static const string fileName;

public:
	static void programmeInitialising();
	static void programmeTerminating();
	static vector<string> returnTask();
};

#endif
