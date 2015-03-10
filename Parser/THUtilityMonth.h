#ifndef THUTILITYMONTH_H
#define THUTILITYMONTH_H

#include <string>
#include <map>


// This class assists THUtility class to map month abbreviation strings
// to integer month and vice versa.
class THUtilityMonth {
public:
	THUtilityMonth();

	int convertMonthFromStringToInt(std::string);
	std::string convertMonthFromIntToString(int);

private:
	static const std::string JAN_STRING;
	static const std::string FEB_STRING;
	static const std::string MAR_STRING;
	static const std::string APR_STRING;
	static const std::string MAY_STRING;
	static const std::string JUN_STRING;
	static const std::string JUL_STRING;
	static const std::string AUG_STRING;
	static const std::string SEP_STRING;
	static const std::string OCT_STRING;
	static const std::string NOV_STRING;
	static const std::string DEC_STRING;
	static const std::string INVALID_MONTH_STRING;


	static const int JAN_INT;
	static const int FEB_INT;
	static const int MAR_INT;
	static const int APR_INT;
	static const int MAY_INT;
	static const int JUN_INT;
	static const int JUL_INT;
	static const int AUG_INT;
	static const int SEP_INT;
	static const int OCT_INT;
	static const int NOV_INT;
	static const int DEC_INT;
	static const int INVALID_MONTH_INT;

	std::map<std::string, int> _stringIntMap;
	std::map<int, std::string> _intStringMap;

	void caseCorrection(std::string&);
};
#endif