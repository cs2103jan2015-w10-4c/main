#ifndef TIMEPARSER_H
#define TIMEPARSER_H
#include <string>
using namespace std;

class TimeParser{

public:
	TimeParser();
	TimeParser(string input);
	string getStartTime();
	string getEndTime();
	int getHour();
	int getMinute();
private:
	string _startTime;
	string _endTime;
	int _hour;
	int _minute;
};
#endif
