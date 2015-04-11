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
	bool isValidDate();
private:
	string _date;
	string _day;
	string _month;
	string _alphaMonth;
	int _integerDay;
	int _integerMonth;
	bool _validDate;
};
#endif
