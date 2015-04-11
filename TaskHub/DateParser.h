//author: A0115399W

#ifndef DATEPARSER_H
#define DATEPARSER_H
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>
using namespace std;

class DateParser{

private:
	string _date;
	string _day;
	string _month;
	string _alphaMonth;
	int _integerDay;
	int _integerMonth;
	bool _validDate;
	
public:
	DateParser();
	DateParser(string input);
	string getDate();
	string getDateReverse();
	string getAlphaMonth();
	int getDay();
	int getMonth();
	bool isValidDate();
	enum DateType {DDMM, DMM, DDM, DM,INVALID};
	DateType determinDateType(string input);
	void checkValidation(string input);
	bool checkIntegerValidation(string input, int digit);
};
#endif
