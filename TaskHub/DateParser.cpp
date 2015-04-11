//author: A0115399W

#include "DateParser.h"
#include <string>
#include <iostream>
using namespace std;

const int LENGTH_OF_FOUR_DIGIT_DATE = 5;
const int LENGTH_OF_THREE_DIGIT_DATE = 4;
const int LENGTH_OF_TWO_DIGIT_DATE = 3;
const int POSITION_ADJUSTMENT_THREE = 3;
const int POSITION_ADJUSTMENT_TWO = 2;
const int POSITION_ADJUSTMENT_ONE = 1;
const int LENGTH_MONTH_DOUBLE = 2;
const int LENGTH_MONTH_SINGLE = 1;
const int LENGTH_DAY_DOUBLE = 2;
const int LENGTH_DAY_SINGLE = 1;
const int LENGTH_ONE_DIGIT = 1;
const string EMPTY_SPACE = " ";
const string SLASH = "/";
const string ZERO = "0";
const string START_OF_DOUBLE = "01";
const string MONTH_END_DOUBLE = "12";
const string DAY_END_DOUBLE = "31";
const string START_OF_SINGLE = "1";
const string END_OF_SINGLE = "9";


DateParser::DateParser(void){
}



DateParser::DateParser(string input){
	//_validDate = false;
	//checkValidation(input);
	//if(_validDate){
		size_t get_date = input.find_first_of(SLASH);
			if(input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
			//  format:  dd/mm
				if(input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
					_date = input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_OF_FOUR_DIGIT_DATE);
					_day = input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_DAY_DOUBLE);
					_month = input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_MONTH_DOUBLE);
					_integerDay = atoi(_day.c_str());
					_integerMonth = atoi(_month.c_str());
				}
			// format:  dd/m
				if(input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) == EMPTY_SPACE){
					_date = input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_OF_THREE_DIGIT_DATE);
					_day = input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_DAY_DOUBLE);
					_month = input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_MONTH_SINGLE);
					_integerDay = atoi(_day.c_str());
					_integerMonth = atoi(_month.c_str());
				}
			
		}
			else{
				if(input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) == EMPTY_SPACE){
				// format: d/mm
					if(input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
						_date = input.substr(get_date-POSITION_ADJUSTMENT_ONE, LENGTH_OF_THREE_DIGIT_DATE);
						_day = ZERO + input.substr(get_date-POSITION_ADJUSTMENT_ONE, LENGTH_DAY_SINGLE);
						_month = input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_MONTH_DOUBLE);
						_integerDay = atoi(_day.c_str());
						_integerMonth = atoi(_month.c_str());
					}
					// format: d/m
					if(input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) == EMPTY_SPACE){
						_date = input.substr(get_date-POSITION_ADJUSTMENT_ONE, LENGTH_OF_TWO_DIGIT_DATE);
						_day = ZERO + input.substr(get_date-POSITION_ADJUSTMENT_ONE, LENGTH_DAY_SINGLE);
						_month = input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_MONTH_SINGLE);
						_integerDay = atoi(_day.c_str());
						_integerMonth = atoi(_month.c_str());
					}
				}
			}
	}




/*DateParser::DateType DateParser::determinDateType(string input){
	DateType dateType;
	size_t get_date = input.find_first_of(SLASH);
	size_t multipleDate = input.find_last_of(SLASH);
	if (get_date != string::npos && get_date == multipleDate){
		if(input.substr(get_date-POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
			if(input.substr(get_date+POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
				dateType = DDMM;
			}
			if(input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
				dateType = DDM;
			}
		}
		else{
			dateType = INVALID;
		}
		if(input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(get_date-POSITION_ADJUSTMENT_ONE, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
			if(input.substr(get_date+POSITION_ADJUSTMENT_THREE, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
				dateType = DMM;
			}
			if(input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_ONE_DIGIT) == EMPTY_SPACE && input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_ONE_DIGIT) != EMPTY_SPACE){
				dateType = DM;
			}
		}
		else{
			dateType = INVALID;
		}
	}
	return dateType;
}

void  DateParser::checkValidation(string input){
	size_t get_date = input.find_first_of(SLASH);
	string doubleDay = input.substr(get_date-POSITION_ADJUSTMENT_TWO, LENGTH_DAY_DOUBLE);
	string doubleMonth = input.substr(get_date+POSITION_ADJUSTMENT_TWO, LENGTH_DAY_DOUBLE);
	string singleDay =  input.substr(get_date-POSITION_ADJUSTMENT_ONE, LENGTH_DAY_SINGLE);
	string singleMonth =  input.substr(get_date+POSITION_ADJUSTMENT_ONE, LENGTH_DAY_SINGLE);
	DateType dateType = determinDateType(input);
	switch(dateType) {
	case DDMM:
		_validDate = checkIntegerValidation(doubleDay, LENGTH_DAY_DOUBLE);
		if(_validDate){
			_validDate = checkIntegerValidation(doubleMonth, LENGTH_MONTH_DOUBLE);
		}
		break;
	case DDM:
		_validDate = checkIntegerValidation(doubleDay, LENGTH_DAY_DOUBLE);
		if(_validDate){
			_validDate = checkIntegerValidation(singleMonth, LENGTH_MONTH_SINGLE);
		}
		break;
	case DMM:
		_validDate = checkIntegerValidation(singleDay, LENGTH_DAY_SINGLE);
		if(_validDate){
			_validDate = checkIntegerValidation(doubleMonth, LENGTH_MONTH_DOUBLE);
		}
		break;
	case DM:
		_validDate = checkIntegerValidation(singleDay, LENGTH_DAY_SINGLE);
		if(_validDate){
			_validDate = checkIntegerValidation(singleMonth, LENGTH_MONTH_SINGLE);
		}
		break;
	case INVALID:
		_validDate = false;
		break;
    }
}

bool DateParser::checkIntegerValidation(string input, int digit){
	bool isInteger = false;
	if(digit == 1){
		if(input >= START_OF_SINGLE && input <= END_OF_SINGLE){
			isInteger = true;
		}
	}
	if(digit == 2){
		if(input >= START_OF_DOUBLE && input <= DAY_END_DOUBLE){
			isInteger = true;
		}
	}
	return isInteger;	
}*/

string DateParser::getDate(){
	return _date;
}

string DateParser::getDateReverse(){
	return _month + SLASH + _day;
}

int DateParser::getDay(){
	return _integerDay;
}

int DateParser::getMonth(){
	return _integerMonth;
}

bool DateParser::isValidDate(){
	return _validDate;
}
