//@author A0111322
// Purpose of this class is to keep track of the actions done by the user over the course of the program's usage

#include "TaskLog.h"

const std::string MESSAGE_TASKLOG_CLEARED = "Logging history has been cleared";

TaskLog::TaskLog(){
	_logFileName = "LogFile.txt";
	readLogFile();
}

TaskLog::~TaskLog(){
	tempLogStorage.clear();
}

// Function updates the log file after each action by the user.
void TaskLog::updateTaskLog(std::string input){
	tempLogStorage.push_back(input);
	updateLogFile();
}

// The function is to get retrieve all prior logging history of the user upon the start up of the program
void TaskLog::readLogFile(){
	std::ifstream openFile;
	std::string tempString;

	tempLogStorage.clear();
	openFile.open(_logFileName.c_str());

	while (getline(openFile, tempString)){
		tempLogStorage.push_back(removeIndexFromString(tempString));
	}
	openFile.close();
}

std::string TaskLog::removeIndexFromString(std::string logString){
	return logString.substr(logString.find_first_of(":") + 2);
}

// Function shows the user the entire logging history
void TaskLog::printTaskLog(){
	std::cout << "Log history:" << std::endl;
	std::cout << getTaskLog();
}

//Function allows the user to clear the entire log file.
void TaskLog::clearTaskLog(){
	tempLogStorage.clear();
	printClearedTaskLogMessage();
}

std::string TaskLog::getTaskLog(){
	std::ostringstream oss;
	std::vector<std::string>::iterator iter;
	int index = 1;

	for (iter = tempLogStorage.begin(); iter != tempLogStorage.end(); iter++){
		oss << index << ": " << *iter;
		if (iter != tempLogStorage.end() - 1){
			oss << std::endl;
			index++;
		}
	}
	return oss.str();
}

void TaskLog::updateLogFile(){
	std::ofstream file;
	file.open(getLogFileName());
	file << getTaskLog();
	
	file.close();
}

void TaskLog::printClearedTaskLogMessage(){
	std::cout << MESSAGE_TASKLOG_CLEARED << std::endl;
}

std::string TaskLog::getLogFileName(){
	return _logFileName;
}
