#ifndef DATEPARSER_H
#define DATEPARSER_H
#include <string>
using namespace std;
class DateParser{

public:
	DateParser();
	DateParser(string input);
	string getDate();
	string getDateReverse();
	int getDay();
	int getMonth();
private:
	string _date;
	string _day;
	string _month;
	int _integerDay;
	int _integerMonth;
};
#endif
