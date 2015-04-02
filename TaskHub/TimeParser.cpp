#include "TimeParser.h"


TimeParser::TimeParser(void){
}

TimeParser::TimeParser(string input){
	size_t timed_Task = input.find("-from");
	size_t ending_time = input.find("-to");
	_startTime = input.substr(timed_Task + 6, 5);
	_endTime = input.substr(ending_time + 4, 5);
	_startHour = atoi(_startTime.substr(0, 2).c_str());
	_startMinute = atoi(_startTime.substr(3, 2).c_str());
	_endHour = atoi(_endTime.substr(0, 2).c_str());
	_endMinute = atoi(_endTime.substr(3, 2).c_str());
}

string TimeParser::getStartTime(){
	return _startTime;
}

string TimeParser::getEndTime(){
	return _endTime;
}


int TimeParser::getStartHour(){
	return _startHour;
}

int TimeParser::getStartMinute(){
	return _startMinute;
}

int TimeParser::getEndHour(){
	return _endHour;
}

int TimeParser::getEndMinute(){
	return _endMinute;
}