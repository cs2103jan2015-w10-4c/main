//@author: A0115399W
#include "TimeParser.h"


TimeParser::TimeParser(void){
}

TimeParser::TimeParser(string input){
	size_t startTime = input.find_first_of(":");
	size_t endTime = input.find_last_of(":");
	 //both start time and end time found, scheduled task
	if(startTime != endTime){  
		_startTime = input.substr(startTime-2, 5);
		_endTime = input.substr(endTime-2, 5);
		_startHour = atoi(_startTime.substr(0, 2).c_str());
		_startMinute = atoi(_startTime.substr(3, 2).c_str());
		_endHour = atoi(_endTime.substr(0, 2).c_str());
		_endMinute = atoi(_endTime.substr(3, 2).c_str());
	}
	//only one time is found, deadline task
	if(startTime == endTime){ 
		_startTime = input.substr(startTime-2, 5);
		_endTime = "";
		_startHour = atoi(_startTime.substr(0, 2).c_str());
		_startMinute = atoi(_startTime.substr(3, 2).c_str());
	}
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