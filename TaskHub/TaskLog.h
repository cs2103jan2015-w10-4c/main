//@author A0111322E

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

class TaskLog{

public:
	TaskLog();
	~TaskLog();
	
	void updateTaskLog(std::string input);
	void printTaskLog();
	void clearTaskLog();

	void readLogFile();
	void updateLogFile();
	void printClearedTaskLogMessage();

	std::string removeIndexFromString(std::string logString);
	std::string getTaskLog();
	std::string getLogFileName();

private:
	char buffer[255];
	std::string _logFileName;
	std::string MESSAGE_TASKLOG_CLEARED;
	std::vector<std::string> tempLogStorage;

};


