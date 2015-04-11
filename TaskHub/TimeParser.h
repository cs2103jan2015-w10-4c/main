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
	int getStartHour();
	int getStartMinute();
	int getEndHour();
	int getEndMinute();
private:
	string _startTime;
	string _endTime;
	int _startHour;
	int _startMinute;
	int _endHour;
	int _endMinute;
};
#endif
