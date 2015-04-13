//@author A0115399W
//**********************************************************
//                        class TimeParser
//     this class will receive input from parser class, and its job is to extract out time in form of string
//     as well as integer and return the values back to parser class. It can return hour and minute seperately.
//
//******************************************************************
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
