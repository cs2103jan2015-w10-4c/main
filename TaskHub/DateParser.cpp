#include "DateParser.h"
#include <string>
using namespace std;

DateParser::DateParser(void){
}

DateParser::DateParser(string input){
	size_t get_date = input.find("/");
	if(input.substr(get_date-2,0) != " "){
		if(input.substr(get_date+2,0) != " "){
			_date = input.substr(get_date-2, 5);
		}
		else{
			if(input.substr(get_date+2,0) == " "){
				_date = input.substr(get_date-2, 4);
			}
		}
		
	}
	else{
		if(input.substr(get_date-2,0) == " "){
			if(input.substr(get_date+2, 0) != " "){
				_date = input.substr(get_date-1, 4);
			}
			else{
				if(input.substr(get_date+2, 0) == " "){
					_date = input.substr(get_date-1, 3);
				}
			}
		}
	}
}

string DateParser::getDate(){
	return _date;
}