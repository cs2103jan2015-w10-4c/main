//author: A0115399W

#include "TimeParser.h"

const string COLON = ":";
const int LENGTH_TWO_DIGIT = 2;
const int LENGTH_TIME = 5;
const int MIN_POSITION = 3;
const int HOUR_POSITION = 0;
const int POSITION_ADJUSTMENT_THREE = 3;
const int LENGTH_ONE_DIGIT = 1;
const string EMPTY_SPACE = " ";
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
	checkValidation(input);
	if(_validTime){
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
}

void TimeParser::checkValidation(string input){
	size_t startTime = input.find_first_of(COLON);
	size_t endTime = input.find_last_of(COLON);
	string startHour = input.substr(startTime-LENGTH_TWO_DIGIT, LENGTH_TWO_DIGIT);
	string startMinute = input.substr(startTime+LENGTH_ONE_DIGIT, LENGTH_TWO_DIGIT);
	string endHour = input.substr(endTime-LENGTH_TWO_DIGIT, LENGTH_TWO_DIGIT);
	string endMinute = input.substr(endTime+LENGTH_ONE_DIGIT, LENGTH_TWO_DIGIT);
	if(startTime != endTime){
		if(input.substr(startTime-POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(startTime-LENGTH_TWO_DIGIT, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
			if(input.substr(startTime+POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(startTime+LENGTH_TWO_DIGIT, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
				_validTime = checkIntegerValidation(startHour);
				if(_validTime){
					checkIntegerValidation(startMinute);
					if(_validTime){
						checkIntegerValidation(endHour);
						if(_validTime){
							checkIntegerValidation(endMinute);
						}
					}
				}
			}
		}
	}
	
	if(startTime == endTime){
		if(input.substr(startTime-POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(startTime-LENGTH_TWO_DIGIT, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
			if(input.substr(startTime+POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(startTime+LENGTH_TWO_DIGIT, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
				_validTime = checkIntegerValidation(startHour);
				if(_validTime){
					checkIntegerValidation(startMinute);
				}
			}
		}
	}

}


bool TimeParser::checkIntegerValidation(string input){
	bool isInteger = false;
	if(input >= HOUR_START && input <= MIN_END){
		isInteger = true;
	}
	return isInteger;
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