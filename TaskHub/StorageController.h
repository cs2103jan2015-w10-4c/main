#ifndef STORAGECONTROLLER_H_
#define STORAGECONTROLLER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Logic.h"
#include "TaskLog.h"

using namespace std;

class StorageController {
private:
	static vector<string> TaskList;
	static std::string _fileName;

public:
	StorageController();
	~StorageController();

	static TaskLog* taskLog; // For logging
	static void constructTaskLog();
	static void destructTaskLog();

	static void programmeInitialising();
	static void programmeTerminating(); // need change to updateSaveFile();
	static void readSaveFile();
	static void promptSaveFile();
	static vector<string> returnTask();

	static void setFileName(std::string fileName);
	static std::string getFileName();
	static std::string convertTaskIntoString();
};

#endif

