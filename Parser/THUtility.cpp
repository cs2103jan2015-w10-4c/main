#include "THUtility.h"
#include "THUtilityMonth.h"
#include "THUtilityTime.h"

using namespace std;

THUtility::THUtility() {
}

int THUtility::convertMonthFromStringToInt(string inputString) {
	return _monthUtility.convertMonthFromStringToInt(inputString);
}

string THUtility::convertMonthFromIntToString(int inputInt) {
	return _monthUtility.convertMonthFromIntToString(inputInt);
}

int THUtility::getCurrentDay() {
	return _timeUtility.getCurrentDay();
}

int THUtility::getCurrentMonth() {
	return _timeUtility.getCurrentMonth();
}

int THUtility::getCurrentYear() {
	return _timeUtility.getCurrentYear();
}

int THUtility::getCurrentMinute() {
	return _timeUtility.getCurrentMinute();
}

int THUtility::getCurrentHour() {
	return _timeUtility.getCurrentHour();
}

