//@author A0115399W
//**********************************************************
//                         class DateParser
//     this class will receive input from parser class, and its job is to extract out date in form of string
//     as well as integer and return the values back to parser class
//
//******************************************************************
#ifndef DATEPARSER_H
#define DATEPARSER_H
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
using namespace std;
class DateParser{

public:
	DateParser();
	DateParser(string input);
	string getDate();
	string getDateReverse();
	string getAlphaMonth();
	int getDay();
	int getMonth();
private:
	string _date;
	string _day;
	string _month;
	string _alphaMonth;
	int _integerDay;
	int _integerMonth;

};
#endif
