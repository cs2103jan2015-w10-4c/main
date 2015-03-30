#include "TimeParser.h"


TimeParser::TimeParser(void){
}

TimeParser::TimeParser(string input){
	size_t timed_Task = input.find("-from");
	size_t ending_time = input.find("-to");
	_startTime = input.substr(timed_Task + 6, 5);
	_endTime = input.substr(ending_time + 4, 5);
<<<<<<< HEAD
	_startHour = atoi(input.substr(timed_Task+6, 2).c_str());
	_startMinute = atoi(input.substr(timed_Task+9, 2).c_str());
	_endHour = atoi(input.substr(ending_time+4, 2).c_str());
	_endMinute = atoi(input.substr(ending_time+7, 2).c_str());
=======
	_hour = atoi(input.substr(timed_Task+6, 2).c_str());
	_minute = atoi(input.substr(timed_Task+9, 2).c_str());
>>>>>>> 406445856a424c95f96b866652307badb6ccb5b3
}

string TimeParser::getStartTime(){
	return _startTime;
}

string TimeParser::getEndTime(){
	return _endTime;
}

<<<<<<< HEAD
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
=======
int TimeParser::getHour(){
	return _hour;
}

int TimeParser::getMinute(){
	return _minute;
>>>>>>> 406445856a424c95f96b866652307badb6ccb5b3
}