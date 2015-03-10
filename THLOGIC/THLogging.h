// author A0115365J
#ifndef THLOGGING_H
#define THLOGGING_H

#include <string>
#include <vector>
using namespace std;

class THLogging {
public:
	static THLogging& getInstance() {
		static THLogging instance;
		return instance;
	}

	void addLog(string);
	void saveLog();


private:
	vector<string> _logMessage;

	THLogging();
};
#endif