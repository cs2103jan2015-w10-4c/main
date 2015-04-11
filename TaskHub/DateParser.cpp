#include "DateParser.h"
#include <string>
#include <iostream>
using namespace std;


const int LENGTH_OF_FOUR_DIGIT_DATE = 5;
const int LENGTH_OF_THREE_DIGIT_DATE = 4;
const int LENGTH_OF_TWO_DIGIT_DATE = 3;
const int POSITION_ADJUSTMENT = 2;

DateParser::DateParser(void){
}

DateParser::DateParser(string input){
	size_t get_date = input.find("/");
	if(get_date != string::npos){

	    if(input.substr(get_date-POSITION_ADJUSTMENT,1) != " "){
		//  format:  dd/mm
			if(input.substr(get_date+POSITION_ADJUSTMENT,1) != " "){
				_date = input.substr(get_date-POSITION_ADJUSTMENT, LENGTH_OF_FOUR_DIGIT_DATE);
				_day = input.substr(get_date-POSITION_ADJUSTMENT,2);
				_month = input.substr(get_date+1, 2);
				_integerDay = atoi(_day.c_str());
				_integerMonth = atoi(_month.c_str());
			}
		// format:  dd/m
			if(input.substr(get_date+2,1) == " "){
				_date = input.substr(get_date-POSITION_ADJUSTMENT, LENGTH_OF_THREE_DIGIT_DATE);
				_day = input.substr(get_date-POSITION_ADJUSTMENT,2);
				_month = input.substr(get_date+1, 1);
				_integerDay = atoi(_day.c_str());
				_integerMonth = atoi(_month.c_str());
			}
			
	}
		else{
			if(input.substr(get_date-POSITION_ADJUSTMENT,1) == " "){
			// format: d/mm
				if(input.substr(get_date+POSITION_ADJUSTMENT, 1) != " "){
					_date = input.substr(get_date-1, LENGTH_OF_THREE_DIGIT_DATE);
					_day = "0" + input.substr(get_date-1, 1);
					_month = input.substr(get_date+1, 2);
					_integerDay = atoi(_day.c_str());
					_integerMonth = atoi(_month.c_str());
				}
				// format: d/m
				if(input.substr(get_date+POSITION_ADJUSTMENT, 1) == " "){
					_date = input.substr(get_date-1, LENGTH_OF_TWO_DIGIT_DATE);
					_day = "0" + input.substr(get_date-1, 1);
					_month = input.substr(get_date+1, 1);
					_integerDay = atoi(_day.c_str());
					   _integerMonth = atoi(_month.c_str());
				}
			}
		}
	}
    //date is not found
    //else if(get_date == string::npos){

  
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