#ifndef DATEPARSER_H
#define DATEPARSER_H
#include <string>
using namespace std;
class DateParser
{
public:
	DateParser();
	DateParser(string input);
	string getDate();
private:
	string _date;
};
#endif
