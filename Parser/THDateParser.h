#ifndef THDATEPASER_H
#define THDATEPARSER_H

#include <string>
#include <vector>
#include "THInputDateCheck.h"

//THDateParser will attempt to parse the dates found in a string using regex.
//Higher priority will be given to dates which contains year.
//Dates which appear later in the string will have precedence over dates which appeared earlier.
//This is based on the assumption that the user will enter the task name first before the dates
//An escape character is provided to prevent potential misinterpretation
//THDateParser will only retain at most 2 important dates found using the precedence rule desribed above.
//The rest of the parsed dates which are not included will be treated as task name.
//THDateParser will return a vector of at most size 2.
//The dates stored in the vector will be in YYYYMMDD digit format.
//The date which appeared later will be stored in a earlier index of the vector

class THDateParser {
public:
	THDateParser();

	void parseDate(std::string);

	void retrieveDate(std::vector<std::string>&);
	std::string retrieveUnusedContent();

private:
	std::string _inputString;
	std::string _unusedContent;

	std::vector<unsigned int> _dateIndex;
	std::vector<std::string> _dateStorage;
	std::vector<std::string> _originalDateStorage;

	int _higherPriorityAdjustment;

	THInputDateCheck _dateChecker;

	void extractDate();
	bool parseWordFormatWithYear(std::string&);
	bool parseDigitFormatWithYear(std::string&);
	bool parseWordFormatWithoutYear(std::string&);
	bool parseDigitFormatWithoutYear(std::string&);
	int determineLastMatchIndex();

	void determineDate();
	void retainTwoImportantDates();
	void allocatePriority();
	void deallocatePriority();
	void sortDatesByAppearance();

	void extractUnusedContent();

	bool isNotEscapeCharacter(char);
};
#endif

