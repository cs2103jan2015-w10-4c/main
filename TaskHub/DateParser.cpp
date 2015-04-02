#include "DateParser.h"
#include <string>
using namespace std;

DateParser::DateParser(void){
}

DateParser::DateParser(string input){
	size_t get_date = input.find("/");
	if(input.substr(get_date-2,1) != " "){
		//  format:  dd/mm
		if(input.substr(get_date+2,1) != " "){
			_date = input.substr(get_date-2, 5);
			_day = atoi(input.substr(get_date-2,2).c_str());
			_month = atoi(input.substr(get_date+1, 2).c_str());
		}
		// format:  dd/m
		else{
			if(input.substr(get_date+2,1) == " "){
				_date = input.substr(get_date-2, 4);
				_day = atoi(input.substr(get_date-2,2).c_str());
				_month = atoi(input.substr(get_date+1, 1).c_str());
			}
		}
		
	}
	else{
		if(input.substr(get_date-2,1) == " "){
			// format: d/mm
			if(input.substr(get_date+2, 1) != " "){
				_date = input.substr(get_date-1, 4);
				_day = atoi(input.substr(get_date-1, 1).c_str());
				_month = atoi(input.substr(get_date+1, 2).c_str());
			}
			// format: d/m
			else{
				if(input.substr(get_date+2, 1) == " "){
					_date = input.substr(get_date-1, 3);
					_day = atoi(input.substr(get_date-1, 1).c_str());
					_month = atoi(input.substr(get_date+1, 1).c_str());
				}
			}
		}
	}
}

string DateParser::getDate(){
	return _date;
}

int DateParser::getDay(){
	return _day;
}

int DateParser::getMonth(){
	return _month;
}