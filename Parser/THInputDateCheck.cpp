#include <string>
#include "THUtility.h"
#include "THInputDateCheck.h"
#include "THLogging.h"

using namespace std;

//The date string will be returned in YYYYMMDD format, thus the size is 2 for MM
const unsigned int STANDARD_MONTH_SIZE = 2;
const string STANDARD_MONTH_SIZE_ADJUSTMENT = "0";

//The date string will be returned in YYYYMMDD format, thus the size is 2 for DD
const unsigned int STANDARD_DAY_SIZE = 2;
const string STANDARD_DAY_SIZE_ADJUSTMENT = "0";

const int FIRST_INDEX_FOR_MONTH = 0;
const int SIZE_MONTH_SHORTHAND = 3;

const int SMALLEST_POSSIBLE_MONTH_INT = 1;
const int LARGEST_POSSIBLE_MONTH_INT = 12;

const int SMALLEST_POSSIBLE_DAY_INT = 1;

const int LARGEST_POSSIBLE_FEB_DAYS_NONLEAPYEAR = 28;
const int LARGEST_POSSIBLE_FEB_DAYS_LEAPYEAR = 29;

//Knuckle months are months that have 31 days
//Non-knuckle months are months that have 30 days
const int LARGEST_POSSIBLE_DAYS_KNUCKLEMONTH = 31;
const int LARGEST_POSSIBLE_DAYS_NONKNUCKLEMONTH = 30;

//To add a year to the date strings, 10000 is added as int.
//This is because the format is YYYYMMDD
const int NEXT_YEAR_ADJUSTMENT = 10000;

const string LOG_ISVALID = "date is valid with output: ";
const string LOG_NOTVALID = "date is not valid";

THInputDateCheck::THInputDateCheck() {
}

//isValidDateWordFormat is used to check if dates such as 23 nov 2014 is valid.
//The method will return true if valid and a string 20141123 in this case.
bool THInputDateCheck::isValidDateWordFormat(string yearString, string monthString, string dayString, string& standardDateFormat) {
	THLogging& Logging = THLogging::getInstance();

	bool isValid = false;

	if(isValidYear(yearString)) {
		if(isValidMonthWordFormat(monthString)) {
			if(isValidDay(dayString)) {
				isValid = true;
				standardDateFormat = composeProjectDate();
			}
		}
	}

	if(isValid) {
		Logging.addLog(LOG_ISVALID + standardDateFormat);
	} else {
		Logging.addLog(LOG_NOTVALID);
	}

	Logging.saveLog();

	return isValid;
}

//isValidDateWordFormatWithoutYear is used to check if dates such as 23 nov is valid.
//The current system year will be used as default for the missing year input.
//The method will return true if valid and a string 20141123 in this case.
bool THInputDateCheck::isValidDateWordFormatWithoutYear(string monthString, string dayString, string& standardDateFormat) {
	THLogging& Logging = THLogging::getInstance();

	bool isValid = false;

	THUtility& utilities = THUtility::getInstance();
	_year = utilities.getCurrentYear();

	if(isValidMonthWordFormat(monthString)) {
		if(isValidDay(dayString)) {
			isValid = true;
			standardDateFormat = composeProjectDate();
		}
	}

	if(isValid) {
		if(isOverdueWithoutYear(standardDateFormat)) {
			setNextYear(standardDateFormat);
		}
	}

	if(isValid) {
		Logging.addLog(LOG_ISVALID + standardDateFormat);
	} else {
		Logging.addLog(LOG_NOTVALID);
	}

	Logging.saveLog();
	
	return isValid;
}

//isValidDateDigitFormat is used to check if dates such as 23/11/2014 is valid.
//The method will return true if valid and a string 20141123 in this case.
bool THInputDateCheck::isValidDateDigitFormat(string yearString, string monthString, string dayString, string& standardDateFormat) {
	THLogging& Logging = THLogging::getInstance();

	bool isValid = false;

	if(isValidYear(yearString)) {
		if(isValidMonthDigitFormat(monthString)) {
			if(isValidDay(dayString)) {
				isValid = true;
				standardDateFormat = composeProjectDate();
			}
		}
	}

	if(isValid) {
		Logging.addLog(LOG_ISVALID + standardDateFormat);
	} else {
		Logging.addLog(LOG_NOTVALID);
	}

	Logging.saveLog();

	return isValid;
}

//isValidDateDigitFormatWithoutYear is used to check if dates such as 23/11 is valid.
//The current system year will be used as default for the missing year input.
//The method will return true if valid and a string 20141123 in this case.
bool THInputDateCheck::isValidDateDigitFormatWithoutYear(string monthString, string dayString, string& standardDateFormat) {
	THLogging& Logging = THLogging::getInstance();

	bool isValid = false;

	THUtility& utilities = THUtility::getInstance();
	_year = utilities.getCurrentYear();

	if(isValidMonthDigitFormat(monthString)) {
		if(isValidDay(dayString)) {
			isValid = true;
			standardDateFormat = composeProjectDate();
		}
	}

	if(isValid) {
		if(isOverdueWithoutYear(standardDateFormat)) {
			setNextYear(standardDateFormat);
		}
	}

	if(isValid) {
		Logging.addLog(LOG_ISVALID + standardDateFormat);
	} else {
		Logging.addLog(LOG_NOTVALID);
	}

	Logging.saveLog();

	return isValid;
}

bool THInputDateCheck::isValidYear(string yearString) {
	bool validStatus = false;

	int inputYear = stringToInt(yearString);
	
	THUtility& utilities = THUtility::getInstance();
	int currentYear = utilities.getCurrentYear();

	if(inputYear >= currentYear) {
		validStatus = true;
		_year = inputYear;
	}

	return validStatus;
}

//isValidMonthWordFormat checks if month in word format, such as January, nov, Dec, is valid month
bool THInputDateCheck::isValidMonthWordFormat(string monthString) {
	bool validStatus = false;

	monthString = monthString.substr(FIRST_INDEX_FOR_MONTH, SIZE_MONTH_SHORTHAND);

	THUtility& utilities = THUtility::getInstance();
	int inputMonth = utilities.convertMonthFromStringToInt(monthString);

	if((inputMonth >= SMALLEST_POSSIBLE_MONTH_INT) && (inputMonth <= LARGEST_POSSIBLE_MONTH_INT)) {
		validStatus = true;
		_month = inputMonth;
	}

	return validStatus;
}

//isValidMonthDigitFormat checks if month in digit format is valid month
bool THInputDateCheck::isValidMonthDigitFormat(string monthString) {
	bool validStatus = false;

	int inputMonth = stringToInt(monthString);

	if((inputMonth >= SMALLEST_POSSIBLE_MONTH_INT) && (inputMonth <= LARGEST_POSSIBLE_MONTH_INT)) {
		validStatus = true;
		_month = inputMonth;
	}

	return validStatus;
}

bool THInputDateCheck::isValidDay(string dayString) {
	bool validStatus = false;
	
	int inputDay = stringToInt(dayString); 

	if(inputDay >= SMALLEST_POSSIBLE_DAY_INT) {
		switch(_month) {
			case 2: {
				if(isLeapYear()) { // We only care about leap years in February 
					if(inputDay <= LARGEST_POSSIBLE_FEB_DAYS_LEAPYEAR) {
						validStatus = true;
						_day = inputDay;
					}
				} else {
					if(inputDay <= LARGEST_POSSIBLE_FEB_DAYS_NONLEAPYEAR) {
						validStatus = true;
						_day = inputDay;
					}
				}
				break;
			}

			case 1: 
			case 3: 
			case 5: 
			case 7: 
			case 8: 
			case 10: 
			case 12: {
				if(inputDay <= LARGEST_POSSIBLE_DAYS_KNUCKLEMONTH) {
					validStatus = true;
					_day = inputDay;
				}
				break;
			}

			case 4: 
			case 6: 
			case 9: 
			case 11: {
				if(inputDay <= LARGEST_POSSIBLE_DAYS_NONKNUCKLEMONTH) {
					validStatus = true;
					_day = inputDay;
				}
				break;
			}

			default: {
				validStatus = false;
				break;
			}
		}
	}

	return validStatus;
}

bool THInputDateCheck::isLeapYear() {
	return ((_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0));
}

//isOverdueWithoutYear checks if the input date without year has already been passed.
//For example, an input of 2 Jan without year specified when the system time is already in Apr will return true
bool THInputDateCheck::isOverdueWithoutYear(string inputDate) {
	int currentDate = getCurrentDateInt();

	return (stringToInt(inputDate) < currentDate);
}

void THInputDateCheck::setNextYear(string& inputDate) {
	int nextYearDate = stringToInt(inputDate) + NEXT_YEAR_ADJUSTMENT;
	
	inputDate = to_string(nextYearDate);
}

int THInputDateCheck::getCurrentDateInt() {
	THUtility& utilities = THUtility::getInstance();

	string yearString = to_string(utilities.getCurrentYear());
	string monthString = to_string(utilities.getCurrentMonth());
	string dayString = to_string(utilities.getCurrentDay());

	if(monthString.size() != STANDARD_MONTH_SIZE) {
			monthString = STANDARD_MONTH_SIZE_ADJUSTMENT + monthString;
		}

	if(dayString.size() != STANDARD_DAY_SIZE) {
		dayString = STANDARD_DAY_SIZE_ADJUSTMENT + dayString;
	}

	string currentDateString = yearString + monthString + dayString;

	return stringToInt(currentDateString);
}

//composeProjectDate will compose the date in a YYYYMMDD digit format
string THInputDateCheck::composeProjectDate() {
	string standardYear = to_string(_year);
	string standardMonth = to_string(_month);
	string standardDay = to_string(_day);

	if(standardMonth.size() != STANDARD_MONTH_SIZE) {
		standardMonth = STANDARD_MONTH_SIZE_ADJUSTMENT + standardMonth;
	}

	if(standardDay.size() != STANDARD_DAY_SIZE) {
		standardDay = STANDARD_DAY_SIZE_ADJUSTMENT + standardDay;
	}

	return standardYear + standardMonth + standardDay;
}

int THInputDateCheck::stringToInt(string inputString) {
	return atoi(inputString.c_str());
}