#include "DateParser.h"
#include <string>
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
	size_t get_date = input.find(SLASH);
	if(get_date != string::npos){
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
	
 }
/*	else{
		SYSTEMTIME lt;
		GetLocalTime(&lt);
		_integerDay = lt.wDay;
		_integerMonth = lt.wMonth;
		ostringstream oss;
		oss << _integerDay;
		_day = oss.str();
		oss.clear();
		oss << _integerDay;
		_month = oss.str();
		oss.clear();
		_date = _day + "/" + _month;
	}*/
}

string DateParser::getDate(){
	return _date;
}

string DateParser::getDateReverse(){
	return _month + "/" + _day;
}

int DateParser::getDay(){
	return _integerDay;
}

int DateParser::getMonth(){
	return _integerMonth;
}

string DateParser::getAlphaMonth(){
	int i=1;
	vector<string> months;
	months.push_back("Jan");
	months.push_back("Feb");
	months.push_back("Mar");
	months.push_back("April");
	months.push_back("May");
	months.push_back("Jun");
	months.push_back("Jul");
	months.push_back("Aug");
	months.push_back("Sept");
	months.push_back("Oct");
	months.push_back("Nov");
	months.push_back("Dec");
	while(i != _integerMonth){
		i++;
	}
	_alphaMonth = months[i-1];

	return _alphaMonth;
}