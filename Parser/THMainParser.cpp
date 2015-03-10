#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include "THMainParser.h"
#include "THCommandParser.h"
#include "THDateParser.h"
#include "THTimeParser.h"
#include "THDateTimeSetter.h"
#include "THCommand.h"
#include "THUtility.h"
#include "THLogging.h"

using namespace std;

const string WHITESPACE_TAB = " \t";

const string LOG_PARSEINPUT = "parseInput is called, received ";
const string LOG_RETRIEVECOMMAND = "retrieveCommand is called";
const string LOG_PARSECOMMANDTYPE = "parseCommandType is called, passing ";
const string LOG_PARSEDATE = "parseDate is called, passing ";
const string LOG_PARSETIME = "parseTime is called, passing ";
const string LOG_PROCESSDATETIME = "processDateTime is called";
const string LOG_COMPOSECOMMAND = "composeCommand is called";
const string LOG_COMPOSECOMMANDDETAIL = "composeCommandDetail is called, returned ";

THMainParser::THMainParser() {
}

void THMainParser::parseInput(string inputString) {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PARSEINPUT + inputString);
	Logging.saveLog();

	_dateStorage.clear();
	_timeStorage.clear();
	_inputString = inputString;
	executeParsing();
}

THCommand THMainParser::retrieveCommand() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_RETRIEVECOMMAND);
	Logging.saveLog();

	return _command;
}

void THMainParser::executeParsing() {
	assert(_dateStorage.empty());
	assert(_timeStorage.empty());

	trimLeadingWhitespace(_inputString);

	parseCommandType();
	parseDate();
	parseTime();
	processDateTime();
	composeCommand();
}
	
void THMainParser::parseCommandType() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PARSECOMMANDTYPE + _inputString);
	Logging.saveLog();

	_commandParser.parseCommand(_inputString);
	_commandType = _commandParser.retrieveCommandType();
	_unusedContent = _commandParser.retrieveUnusedContent();
}
	
void THMainParser::parseDate() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PARSEDATE + _unusedContent);
	Logging.saveLog();

	_dateParser.parseDate(_unusedContent);
	_dateParser.retrieveDate(_dateStorage);
	_unusedContent = _dateParser.retrieveUnusedContent();
}
	
void THMainParser::parseTime() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PARSETIME + _unusedContent);
	Logging.saveLog();

	_timeParser.parseTime(_unusedContent);
	_timeParser.retrieveTime(_timeStorage);
	_unusedContent = _timeParser.retrieveUnusedContent();
}

void THMainParser::processDateTime() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PROCESSDATETIME);
	Logging.saveLog();

	_dateTimeSetter.processDateTime(_dateStorage, _timeStorage);
}

void THMainParser::composeCommand() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_COMPOSECOMMAND);
	Logging.saveLog();

	_command.clearCommand();
	_command.setCommand(_commandType);
	composeCommandDetail();

	if(_dateStorage.size() > 0) {
		_command.setDate1(_dateStorage[0]);
	}
	if(_timeStorage.size() > 0) {
		_command.setTime1(_timeStorage[0]);
	}
	if(_dateStorage.size() > 1) {
		_command.setDate2(_dateStorage[1]);
	}
	if(_timeStorage.size() > 1) {
		_command.setTime2(_timeStorage[1]);
	}
}

//The unused content after parsing will all be treated as task name.
//The extra whitespaces are removed and each token are treated as a standalone word.
void THMainParser::composeCommandDetail() {
	_unusedContent.erase(remove(_unusedContent.begin(), _unusedContent.end(), '\\'), _unusedContent.end());
	istringstream iss(_unusedContent);

	string unusedToken;
	vector<string> unusedTokenStorage;

	while(iss >> unusedToken) {
		unusedTokenStorage.push_back(unusedToken);
	}

	string detailString;

	for(unsigned int i = 0; i != unusedTokenStorage.size(); i++) {
		if(i == unusedTokenStorage.size() - 1) {
			detailString = detailString + unusedTokenStorage[i];
		} else {
			detailString = detailString + unusedTokenStorage[i] + " ";
		}
	}

	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_COMPOSECOMMANDDETAIL + detailString);
	Logging.saveLog();

	_command.setDetail(detailString);
}

void THMainParser::trimLeadingWhitespace(string& input) {
	unsigned int firstNonSpaceIndex = input.string::find_first_not_of(WHITESPACE_TAB);

	if(firstNonSpaceIndex != string::npos) {
		input = input.substr(firstNonSpaceIndex);
	} else {
		input.clear();
	}
}