#ifndef DATEPARSER_H
#define DATEPARSER_H
#include <string>
using namespace std;
class DateParser{

public:
	DateParser();
	DateParser(string input);
	string getDate();
	int getDay();
	int getMonth();
private:
	string _date;
	int _day;
	int _month;
};
#endif
