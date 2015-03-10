
#ifndef THCONVERTER_H
#define THCONVERTER_H

#include <sstream>
#include <string>

#include "THCommand.h"
#include "THUtility.h"
#include "THLogging.h"

// Do the mutual conversions among system time & date, 

class THConverter{
public:
	THConverter();
	
	void convertIntTimeToString (int, int, string&);
	void convertIntDateToString (int, int, int, string&);
	void convertStringDataToInt (string, int&, int&, int&);
	void convertTimeStringToInt (string, int&, int&);
	void formatDateForDisplay   (string&);
	void formatTimeForDisplay   (string&);
	
private:
	string getFormatedTime    (int, int);
	string getFormatedDate    (int, int, int);
	bool        isSingleDigit      (int);
	int         convertStringToInt (string);

	static const int            STRING_StartING_POSITION;
    static const int            MAX_SINGLE_DIGIT;          
	static const int			DIGIT_MID_NIGHT;
	static const int			DIGIT_NOON_HOUR;
	static const int			DIGIT_NOON_MINUTE;
	static const int			DIGIT_MID_NIGHT_TO_MERIDIEM;
	static const int            YEAR_LENGTH;
	static const int            MONTH_LENGTH;
	static const int            DAY_LENGTH;
	static const int            HOUR_LENGTH;
	static const int            MINUTE_LENGTH;


	static const string    LABEL_MORNING;
	static const string    LABEL_NOON;
    static const string    LABEL_AFTERNOON;
	static const string    LABEL_MID_NIGHT;
	static const string    LABEL_TO_DOUBLE_DIGIT;
	static const string    LABEL_COLON;
	static const string    LABEL_SPACE;
	static const string    EMPTY_CONTENT;
	
};
#endif
