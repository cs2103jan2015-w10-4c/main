#include "DateParser.h"
#include <string>
using namespace std;

DateParser::DateParser(void){
}

DateParser::DateParser(string input){
	size_t get_date = input.find("/");
	if(get_date != string::npos){

	  if(input.substr(get_date-2,1) != " "){
		//  format:  dd/mm
		if(input.substr(get_date+2,1) != " "){
			_date = input.substr(get_date-2, 5);
			_day = input.substr(get_date-2,2);
			_month = input.substr(get_date+1, 2);
			_integerDay = atoi(_day.c_str());
			_integerMonth = atoi(_month.c_str());
		}
		// format:  dd/m
		else{
			if(input.substr(get_date+2,1) == " "){
				_date = input.substr(get_date-2, 4);
				_day = input.substr(get_date-2,2);
				_month = input.substr(get_date+1, 1);
				_integerDay = atoi(_day.c_str());
			    _integerMonth = atoi(_month.c_str());
			}
		}
		
	}
	else{
		if(input.substr(get_date-2,1) == " "){
			// format: d/mm
			if(input.substr(get_date+2, 1) != " "){
				_date = input.substr(get_date-1, 4);
				_day = input.substr(get_date-1, 1);
				_month = input.substr(get_date+1, 2);
				_integerDay = atoi(_day.c_str());
			    _integerMonth = atoi(_month.c_str());
			}
			// format: d/m
			else{
				if(input.substr(get_date+2, 1) == " "){
					_date = input.substr(get_date-1, 3);
					_day = input.substr(get_date-1, 1);
					_month = input.substr(get_date+1, 1);
					_integerDay = atoi(_day.c_str());
			        _integerMonth = atoi(_month.c_str());
				}
			}
		}
	}
  }
	else{
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
	}
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