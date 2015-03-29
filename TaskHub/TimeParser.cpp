#include "TimeParser.h"


TimeParser::TimeParser(void){
}

TimeParser::TimeParser(string input){
	size_t timed_Task = input.find("-from");
	size_t ending_time = input.find("-to");
	_startTime = input.substr(timed_Task + 6, 5);
	_endTime = input.substr(ending_time + 4, 5);
	_hour = atoi(input.substr(timed_Task+6, 2).c_str());
	_minute = atoi(input.substr(timed_Task+9, 2).c_str());
}

string TimeParser::getStartTime(){
	return _startTime;
}

string TimeParser::getEndTime(){
	return _endTime;
}

int TimeParser::getHour(){
	return _hour;
}

int TimeParser::getMinute(){
	return _minute;
}