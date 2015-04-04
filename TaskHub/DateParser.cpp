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