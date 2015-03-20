#include "DateParser.h"
#include <string>
using namespace std;

DateParser::DateParser(void){
}

DateParser::DateParser(string input){
	size_t get_date = input.find("/");
	_date = input.substr(get_date - 2, 5);
}

string DateParser::getDate(){
	return _date;
}