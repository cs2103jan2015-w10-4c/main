
#include <iostream>
#include <string>
#include <fstream>
#include "THLogging.h"

using namespace std;

const string LOG_FILENAME = "logFile.txt";

THLogging::THLogging() {
}

void THLogging::addLog(string newLog) {
	_logMessage.push_back(newLog);
}

void THLogging::saveLog() {
	ofstream writeFile(LOG_FILENAME.c_str());

	for(unsigned int i = 0; i < _logMessage.size(); i++) {
		writeFile << _logMessage[i] << Endl;		
	}

	writeFile.close();
}
