#include "TimeParser.h"
const string COLON = ":";
const int LENGTH_TWO_DIGIT = 2;
const int LENGTH_TIME = 5;
const int MIN_POSITION = 3;
const int HOUR_POSITION = 0;
const string MIN_START = "00";
const string MIN_END = "59";
const string HOUR_START = "00";
const string HOUR_END = "23";

TimeParser::TimeParser(void){
}

TimeParser::TimeParser(string input){
	_validTime = false;
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
		if(_startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) >= HOUR_START && _startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) <= HOUR_END && _startTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT) >= MIN_START && _startTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT) <= MIN_END && _endTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) >= HOUR_START && _endTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) <= HOUR_END && _endTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT) >= MIN_START && _endTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT) <= MIN_END){
			_validTime = true;
		}
	}
	//only one time is found, deadline task
	if(startTime == endTime){ 
		_startTime = input.substr(startTime-LENGTH_TWO_DIGIT, LENGTH_TIME);
		_endTime = "";
		_startHour = atoi(_startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT).c_str());
		_startMinute = atoi(_startTime.substr(MIN_POSITION, LENGTH_TWO_DIGIT).c_str());
		if(_startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) >= MIN_START && _startTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) <= MIN_END && _endTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) >= HOUR_START && _endTime.substr(HOUR_POSITION, LENGTH_TWO_DIGIT) <= HOUR_END){
			_validTime = true;
		}
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

bool TimeParser::isValidTime(){
	return _validTime;
}