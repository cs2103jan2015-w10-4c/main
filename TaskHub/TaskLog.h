//@author A0111322E
//
//	This class is meant for logging and the tracking of the user's actions throughout the course
//	of his/her usage of TaskHub.
//	
//	It will also keep track of any errors that have been executed within the different layers of 
//	TaskHub's architecture. It is standardised that the log file will be saved in the same folder 
//	of the TaskHub application and named as 'LogFile.txt', for easier access for the user.
//

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


