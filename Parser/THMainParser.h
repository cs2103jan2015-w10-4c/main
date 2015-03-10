#ifndef THMAINPARSER_H
#define THMAINPARSER_H

#include <string>
#include <vector>
#include "THCommandParser.h"
#include "THDateParser.h"
#include "THTimeParser.h"
#include "THDateTimeSetter.h"
#include "THCommand.h"
#include "THUtility.h"

//THMainParser is the coordinating class that schedules the operations of parsing
//THMainParser will accept the user input through a string
//The order of parsing is as follows:
//CommandType, dates then time
//THMainParser will then make use of THDateTimeSetter to sort the dates and time
//Finally, THMainParser will compose the THCommand object to return to Logic.
//The unused content after parsing will all be treated as task name.
//The dates and time are stored as strings within THCommand with the format being YYYYMMDD and HHMM respectively.

class THMainParser {
public:
	THMainParser();

	void parseInput(std::string);
	THCommand retrieveCommand();

private:
	std::string _inputString;

	THUtility::CommandType _commandType;
	std::string _unusedContent;
	std::vector<std::string> _dateStorage;
	std::vector<std::string> _timeStorage;

	THCommandParser _commandParser;
	THDateParser _dateParser;
	THTimeParser _timeParser;
	THDateTimeSetter _dateTimeSetter;
	THCommand _command;

	void executeParsing();
	void parseCommandType();
	void parseDate();
	void parseTime();
	void processDateTime();
	void composeCommand();
	void composeCommandDetail();

	void trimLeadingWhitespace(std::string&);
};
#endif