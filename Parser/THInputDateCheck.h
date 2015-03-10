//@author A0097547M

#ifndef THInputDateCheck_H
#define THInputDateCheck_H

#include <string>

//THInputDateCheck is mainly used by THDateParser to check if the dates that matched the regexs are valid
//THInputDateCheck will account for leap years when checking
//When the year is not given, THInputDateCheck will set the year as the current system year
//When the input date is already overdue, then THInputDateCheck will adjust it to the nearest year that is not yet overdue
//THInputDateCheck will then return the date in YYYYMMDD digit format through the reference string provided
//THInputDateCheck will also return a bool to denote whether or not the check has passed

class THInputDateCheck {
public:
	THInputDateCheck();

	bool isValidDateWordFormat(std::string, std::string, std::string, std::string&);
	bool isValidDateWordFormatWithoutYear(std::string, std::string, std::string&);
	bool isValidDateDigitFormat(std::string, std::string, std::string, std::string&);
	bool isValidDateDigitFormatWithoutYear(std::string, std::string, std::string&);

private:
	int _year;
	int _month;
	int _day;

	bool isValidYear(std::string);
	bool isValidMonthWordFormat(std::string);
	bool isValidMonthDigitFormat(std::string);
	bool isValidDay(std::string);
	bool isLeapYear();
	bool isNextYear();

	bool isOverdueWithoutYear(std::string);
	void setNextYear(std::string&);
	int getCurrentDateInt();

	std::string composeProjectDate();
	int stringToInt(std::string);
};
#endif

