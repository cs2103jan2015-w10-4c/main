#include "THConverter.h"


using namespace std;

const int    THConverter::STRING_StartING_POSITION      = 0;
const int    THConverter::MAX_SINGLE_DIGIT              = 9;
const int	 THConverter::DIGIT_MID_NIGHT				= 0;
const int	 THConverter::DIGIT_NOON_HOUR			    = 12;
const int	 THConverter::DIGIT_NOON_MINUTE				= 0;
const int    THConverter::DIGIT_MID_NIGHT_TO_MERIDIEM   = 12;
const int    THConverter::YEAR_LENGTH                   = 4;
const int    THConverter::MONTH_LENGTH                  = 2;
const int    THConverter::DAY_LENGTH                    = 2;
const int    THConverter::HOUR_LENGTH                   = 2;
const int    THConverter::MINUTE_LENGTH                 = 2;


const string THConverter::LABEL_MORNING                 = "AM";
const string THConverter::LABEL_NOON                    = "NN";
const string THConverter::LABEL_AFTERNOON               = "PM";
const string THConverter::LABEL_MID_NIGHT               = "MN";
const string THConverter::LABEL_TO_DOUBLE_DIGIT = "0";
const string THConverter::LABEL_COLON                   = ":";
const string THConverter::LABEL_SPACE                   = " ";


THConverter::THConverter() {
}



// Change the format of the tasktime string stored in task 
// to the desired display format on the GUI.
// e.g. from "1215" to "12:15pm"

void THConverter::formatTimeForDisplay(string& taskTime)
{
	string hourString, minuteString;

	if(taskTime.empty()) {
		return;
	} else {
		hourString   = taskTime.substr(STRING_StartING_POSITION, HOUR_LENGTH);
		minuteString = taskTime.substr(HOUR_LENGTH, MINUTE_LENGTH);
	}

	int hour   = convertStringToInt(hourString);
	int minute = convertStringToInt(minuteString);
	
	taskTime = getFormatedTime(hour, minute);
}


// Convert the integer hour and minute to string format
// Output format is "hhmm" which is a string of size 4.


void THConverter::convertIntTimeToString(int hour, int minute, string& timeString){
	ostringstream oss;

	if(!isSingleDigit(hour) && !isSingleDigit(minute)) {
		oss << hour << minute;
	} else if(isSingleDigit(hour) && !isSingleDigit(minute)) {
		oss << LABEL_TO_DOUBLE_DIGIT << hour << minute;
	} else if(!isSingleDigit(hour) && isSingleDigit(minute)) {
		oss << hour << LABEL_TO_DOUBLE_DIGIT << minute;
	} else {
		oss << LABEL_TO_DOUBLE_DIGIT << hour << LABEL_TO_DOUBLE_DIGIT << minute;
	}

	timeString = oss.str();
}

// Convert the integer year, month and day to a string
// Output format is "yyyymmdd" which is a string of size 8

void THConverter::convertIntDateToString(int day, int month, int year, string& dateString){

	ostringstream oss;

	if(!isSingleDigit(month) && !isSingleDigit(day)) {
		oss << year << month << day; 
	} else if(isSingleDigit(month) && !isSingleDigit(day)) {
		oss << year << LABEL_TO_DOUBLE_DIGIT<< month << day;
	} else if(!isSingleDigit(month) && isSingleDigit(day)) {
		oss << year << month << LABEL_TO_DOUBLE_DIGIT << day;
	} else {
		oss << year << LABEL_TO_DOUBLE_DIGIT << month << LABEL_TO_DOUBLE_DIGIT << day;
	}

	dateString = oss.str();
}


// Extract year, month& day from dateString in the format of "yyyymmdd"


void THConverter::convertStringDataToInt(string dateString, int& day, int& month, int& year){
	if(!dateString.empty()) {
		string yearString  = dateString.substr(STRING_StartING_POSITION, YEAR_LENGTH);
		string monthString = dateString.substr(YEAR_LENGTH, MONTH_LENGTH);
		string dayString   = dateString.substr(YEAR_LENGTH + MONTH_LENGTH, DAY_LENGTH);
		
		year  = convertStringToInt(yearString);
		month = convertStringToInt(monthString);
		day   = convertStringToInt(dayString);
	
	} else {
		return;
	}
}

// Extract integer hour& minute from timeString in the format of "hhmm"


void THConverter::convertTimeStringToInt(string timeString, int& hour, int& minute) {
	if(!timeString.empty()) {
		string hourString   = timeString.substr(STRING_StartING_POSITION, HOUR_LENGTH);
		string minuteString = timeString.substr(HOUR_LENGTH, MINUTE_LENGTH);
		hour   = convertStringToInt(hourString);
		minute = convertStringToInt(minuteString);
	} else {
		return;
	}
}
	

// This method transform integer day, month, and year to
// a date string for display.
string THConverter::getFormatedDate(int day, int month, int year){
	THUtility& monthTHUtility = THUtility::getInstance();

	string monthString = monthTHUtility.convertMonthFromIntToString(month);

	ostringstream oss;

	if (day > MAX_SINGLE_DIGIT) {
		oss << day <<LABEL_SPACE<< monthString <<LABEL_SPACE<< year;
	} else {
		oss << LABEL_TO_DOUBLE_DIGIT << day <<LABEL_SPACE<< monthString << LABEL_SPACE << year;
	}
	return oss.str();
}

bool THConverter::isSingleDigit(int number)
{
	bool isSingleDigit = true;
	if(number > MAX_SINGLE_DIGIT) {
		isSingleDigit = false;
	}
	return isSingleDigit;
}

int THConverter::convertStringToInt(string convertString) {
	return atoi(convertString.c_str());
}

// This method transform integer hour and minute to
// a time string for display.
string THConverter::getFormatedTime(int hour, int minute) {
	ostringstream oss;
	string        period;

	if(hour < DIGIT_NOON_HOUR) {
		period = LABEL_MORNING;
	}

	if(hour > DIGIT_NOON_HOUR) {
		period = LABEL_AFTERNOON;
	}

	if((hour == DIGIT_NOON_HOUR) && (minute != DIGIT_NOON_MINUTE)) {
		period = LABEL_AFTERNOON;
	}

	if((hour == DIGIT_NOON_HOUR) && (minute == DIGIT_NOON_MINUTE)) {
		period = LABEL_NOON;
	}

	if((hour == DIGIT_MID_NIGHT) && (minute == DIGIT_MID_NIGHT)) {
		period = LABEL_MID_NIGHT;
	}

	if(hour == DIGIT_MID_NIGHT) {
		hour = hour + DIGIT_MID_NIGHT_TO_MERIDIEM;
	}

	if(hour > DIGIT_NOON_HOUR) {
		hour = hour - DIGIT_NOON_HOUR;
	}

	if (hour > MAX_SINGLE_DIGIT && minute > MAX_SINGLE_DIGIT) {
		oss << hour << LABEL_COLON << minute << period;
	} 
	
	if (hour > MAX_SINGLE_DIGIT && minute <= MAX_SINGLE_DIGIT) {
		oss << hour << LABEL_COLON << LABEL_TO_DOUBLE_DIGIT << minute << period;
	} 
	
	if (hour <= MAX_SINGLE_DIGIT && minute > MAX_SINGLE_DIGIT) {
		oss << LABEL_TO_DOUBLE_DIGIT << hour << LABEL_COLON << minute << period;
	} 
	
	if (hour <= MAX_SINGLE_DIGIT && minute <= MAX_SINGLE_DIGIT) {
		oss << LABEL_TO_DOUBLE_DIGIT << hour << LABEL_COLON << LABEL_TO_DOUBLE_DIGIT << minute << period;
	}

	return oss.str();
}

// Change the format of the taskdate string stored in task 
// to the desired display format on the GUI.
// e.g. from "20131214" to "14 Dec 2013

void THConverter::formatDateForDisplay(string& taskDate)
{
	string yearString, monthString, dayString;

	if(taskDate.empty()) {
		return;
	} else {
		yearString  = taskDate.substr(STRING_StartING_POSITION , YEAR_LENGTH);
		monthString = taskDate.substr(YEAR_LENGTH, MONTH_LENGTH);
		dayString   = taskDate.substr(YEAR_LENGTH + MONTH_LENGTH, DAY_LENGTH);
	}

	int year  = convertStringToInt(yearString);
	int month = convertStringToInt(monthString);
	int day   = convertStringToInt(dayString);

	taskDate = getFormatedDate(day, month, year);
}