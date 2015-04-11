#include "TimeParser.h"
const string COLON = ":";
const int LENGTH_TWO_DIGIT = 2;
const int LENGTH_TIME = 5;
const int MIN_POSITION = 3;
const int HOUR_POSITION = 0;

TimeParser::TimeParser(void){
}

TimeParser::TimeParser(string input){
	size_t startTime = input.find_first_of(COLON);
	size_t endTime = input.find_last_of(COLON);
	 //both start time and end time found, scheduled task
	if(startTime != endTime){  
		_startTime = input.substr(startTime-LENGTH_TWO_DIGIT, LENGTH_TIME);
		_endTime = input.substr(endTime-LENGTH_TWO_DIGIT, LENGTH_TIME);
		_startHour = atoi(_startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT).c_str());
		_startMinute = atoi(_startTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT).c_str());
		_endHour = atoi(_endTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT).c_str());
		_endMinute = atoi(_endTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT).c_str());
	}
	//only one time is found, deadline task
	if(startTime == endTime){ 
		_startTime = input.substr(startTime-LENGTH_TWO_DIGIT, LENGTH_TIME);
		_endTime = "";
		_startHour = atoi(_startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT).c_str());
		_startMinute = atoi(_startTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT).c_str());
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