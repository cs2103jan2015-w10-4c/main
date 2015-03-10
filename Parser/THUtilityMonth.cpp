#include <cctype>
#include <string>
#include <map>
#include "THUtilityMonth.h"

#include <iostream>

using namespace std;

const string THUtilityMonth::JAN_STRING = "Jan";
const string THUtilityMonth::FEB_STRING = "Feb";
const string THUtilityMonth::MAR_STRING = "Mar";
const string THUtilityMonth::APR_STRING = "Apr";
const string THUtilityMonth::MAY_STRING = "May";
const string THUtilityMonth::JUN_STRING = "Jun";
const string THUtilityMonth::JUL_STRING = "Jul";
const string THUtilityMonth::AUG_STRING = "Aug";
const string THUtilityMonth::SEP_STRING = "Sep";
const string THUtilityMonth::OCT_STRING = "Oct";
const string THUtilityMonth::NOV_STRING = "Nov";
const string THUtilityMonth::DEC_STRING = "Dec";
const string THUtilityMonth::INVALID_MONTH_STRING = "";

const int THUtilityMonth::JAN_INT = 1;
const int THUtilityMonth::FEB_INT = 2;
const int THUtilityMonth::MAR_INT = 3;
const int THUtilityMonth::APR_INT = 4;
const int THUtilityMonth::MAY_INT = 5;
const int THUtilityMonth::JUN_INT = 6;
const int THUtilityMonth::JUL_INT = 7;
const int THUtilityMonth::AUG_INT = 8;
const int THUtilityMonth::SEP_INT = 9;
const int THUtilityMonth::OCT_INT = 10;
const int THUtilityMonth::NOV_INT = 11;
const int THUtilityMonth::DEC_INT = 12;
const int THUtilityMonth::INVALID_MONTH_INT = 0;

const int FIRST_CHAR_INDEX = 0;

THUtilityMonth::THUtilityMonth() {
	_stringIntMap[JAN_STRING] = JAN_INT;
	_stringIntMap[FEB_STRING] = FEB_INT;
	_stringIntMap[MAR_STRING] = MAR_INT;
	_stringIntMap[APR_STRING] = APR_INT;
	_stringIntMap[MAY_STRING] = MAY_INT;
	_stringIntMap[JUN_STRING] = JUN_INT;
	_stringIntMap[JUL_STRING] = JUL_INT;
	_stringIntMap[AUG_STRING] = AUG_INT;
	_stringIntMap[SEP_STRING] = SEP_INT;
	_stringIntMap[OCT_STRING] = OCT_INT;
	_stringIntMap[NOV_STRING] = NOV_INT;
	_stringIntMap[DEC_STRING] = DEC_INT;

	_intStringMap[JAN_INT] = JAN_STRING;
	_intStringMap[FEB_INT] = FEB_STRING;
	_intStringMap[MAR_INT] = MAR_STRING;
	_intStringMap[APR_INT] = APR_STRING;
	_intStringMap[MAY_INT] = MAY_STRING;
	_intStringMap[JUN_INT] = JUN_STRING;
	_intStringMap[JUL_INT] = JUL_STRING;
	_intStringMap[AUG_INT] = AUG_STRING;
	_intStringMap[SEP_INT] = SEP_STRING;
	_intStringMap[OCT_INT] = OCT_STRING;
	_intStringMap[NOV_INT] = NOV_STRING;
	_intStringMap[DEC_INT] = DEC_STRING;
}

// maps the month abbreviation string to a integer month
int THUtilityMonth::convertMonthFromStringToInt(string inputString) {
	int monthInt;

	caseCorrection(inputString);

	if(_stringIntMap.count(inputString)) {
		monthInt = _stringIntMap[inputString];
	} else {
		monthInt = INVALID_MONTH_INT;
	}

	return monthInt;
}

// converts integer month to a abbreviation month string
string THUtilityMonth::convertMonthFromIntToString(int inputInt) {
	string monthString;

	if(_intStringMap.count(inputInt)) {
		monthString = _intStringMap[inputInt];
	} else {
		monthString = INVALID_MONTH_STRING;
	}

	return monthString;
}


// convert the uppercase letter in the month abbreviation string
// to lowercase.
void THUtilityMonth::caseCorrection(string& inputString) {
	inputString[FIRST_CHAR_INDEX] = toupper(inputString[FIRST_CHAR_INDEX]);

	for(unsigned int i = 1; i != inputString.size(); i++) {
		inputString[i] = tolower(inputString[i]);
	}
}