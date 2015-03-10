#include <ctime>
#include "THUtilityTime.h"

using namespace std;

const int THUtilityTime::SYSTEM_MONTH_ADJUSTMENT = 1;
const int THUtilityTime::SYSTEM_YEAR_ADJUSTMENT = 1900;

THUtilityTime::THUtilityTime() {
}

int THUtilityTime::getCurrentDay() {
	retrieveDetailsFromSystem();
	return _currentDay;
}

int THUtilityTime::getCurrentMonth() {
	retrieveDetailsFromSystem();
	return _currentMonth;
}

int THUtilityTime::getCurrentYear() {
	retrieveDetailsFromSystem();
	return _currentYear;
}

int THUtilityTime::getCurrentMinute() {
	retrieveDetailsFromSystem();
	return _currentMinute;
}

int THUtilityTime::getCurrentHour() {
	retrieveDetailsFromSystem();
	return _currentHour;
}


// retrieve system time and adjust the private attributes accordingly
void THUtilityTime::retrieveDetailsFromSystem() {
	time_t rawTime = time(NULL);
	struct tm timeInformation;
	localtime_s(&timeInformation, &rawTime);

	_currentDay = timeInformation.tm_mday;
	_currentMonth = timeInformation.tm_mon + SYSTEM_MONTH_ADJUSTMENT;
	_currentYear = timeInformation.tm_year + SYSTEM_YEAR_ADJUSTMENT;
	_currentMinute = timeInformation.tm_min;
	_currentHour = timeInformation.tm_hour;
}