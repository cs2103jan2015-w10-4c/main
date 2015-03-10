//@author A0097547M

#ifndef THTIMEPARSER_H
#define THTIMEPARSER_H

#include <string>
#include <vector>

//THTimeParser will attempt to parse the time found in a string using regex.
//Time which appear later in the string will have precedence over time which appeared earlier.
//This is based on the assumption that the user will enter the task name first before the time
//An escape character is provided to prevent potential misinterpretation
//THTimeParser will only retain at most 2 important time found using the precedence rule desribed above.
//The rest of the parsed time which are not included will be treated as task name.
//THTimeParser will return a vector of at most size 2.
//The time stored in the vector will be in HHMM digit format.
//The time which appeared later will be stored in a earlier index of the vector

class THTimeParser {
public:
	THTimeParser();

	void parseTime(std::string);
	void retrieveTime(std::vector<std::string>&);
	std::string retrieveUnusedContent();

private:
	std::string _inputString;
	std::string _unusedContent;
	std::vector<int> _timeIndex;
	std::vector<std::string> _timeStorage;
	std::vector<std::string> _originalTimeStorage;

	void extractTime();
	bool parseMeridiemFormat(std::string&);
	bool parse24HFormat(std::string&);
	int determineLastMatchIndex();

	bool isValidMeridiemFormat(std::string, std::string, std::string, std::string&);
	bool isAnteMeridiem(std::string);
	bool isPostMeridiem(std::string);
	bool isMidnightMeridiem(std::string, std::string);
	bool isNoonMeridiem(std::string, std::string);

	std::string composeAnteMeridiem(std::string, std::string);
	std::string composePostMeridiem(std::string, std::string);
	std::string composeMidnightMeridiem(std::string);
	std::string composeNoonMeridiem(std::string);

	void determineTime();
	void retainTwoImportantTime();
	void sortTimeByAppearance();

	void extractUnusedContent();

	bool isNotEscapeCharacter(char);

	void toUpperCase(std::string&);
	int stringToInt(std::string);
	std::string intToString(int);

};
#endif