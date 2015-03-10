//@author A0097547M

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <cassert>
#include "THTimeParser.h"
#include "THLogging.h"

using namespace std;

//meridiem format refers to time which have am, pm, mn, nn.
//acceptable formats include:
//7am 7pm 12mn 12nn 7.30am 7:30am 7:30 am
//24H format refers to time written in the following format:
//2359h, there must be an accompanying h
//the regex will automatically ignore time which are invalid
//For example, 2899h or 13pm
const regex timeMeridiemFormat("\\b([0]?[1-9]|1[0-2])([:.]?([0-5][\\d]))?\\s?([ap]m|mn|nn)\\b", regex_constants::icase);
const regex time24HFormat("\\b([01][\\d]|2[0-3])[:.]?([0-5][\\d]\\s?)h\\b", regex_constants::icase);

//These indexes are used to locate information stored within the smatch
const unsigned int MATCH_INDEX = 0;
const unsigned int MERIDIEM_HOUR_INDEX = 1;
const unsigned int MERIDIEM_MINUTE_INDEX = 3;
const unsigned int MERIDIEM_AMPM_INDEX = 4;
const unsigned int DIGIT_24H_HOUR_INDEX = 1;
const unsigned int DIGIT_24H_MINUTE_INDEX = 2;

//These are common strings needed for meridiem format
const string MIDNIGHT_MERIDIEM_HOUR = "12";
const string NOON_MERIDIEM_HOUR = "12";
const string ANTE_MERIDIEM = "AM";
const string POST_MERIDIEM = "PM";
const string MIDNIGHT_MERIDIEM = "MN";
const string NOON_MERIDIEM = "NN";

//These are common strings needed for 24H format
const string MIDNIGHT_DIGIT_HOUR = "00";
const string MIDNIGHT_DIGIT_MINUTE = "00";
const string NOON_DIGIT_HOUR = "12";
const string NOON_DIGIT_MINUTE = "00";

//The time string will be stored in HHMM format, thus the size for HH is 2
const unsigned int STANDARD_HOUR_SIZE = 2;
const string STANDARD_HOUR_SIZE_ADJUSTMENT = "0";

//The time string will be stored in HHMM format, thus the size for MM is 2
const unsigned int STANDARD_MINUTE_SIZE = 2;
const string STANDARD_MINUTE_SIZE_ADJUSTMENT = "0";

//These are int values required to convert the time from meridiem format to 24H format
const int MIDNIGHT_TO_ZERO_ADJUSTMENT = 12;
const int POST_MERIDIEM_TO_DIGIT_ADJUSTMENT = 12;
const int NUMBER_HOURS_IN_DAY = 24;
const int MIDNIGHT_HOUR_INT = 0;

const unsigned int FIRST_TIME_INDEX = 0;
const unsigned int SECOND_TIME_INDEX = 1;

const int DEFAULT_LAST_MATCH_INDEX = 0;
const int DEFAULT_FIRST_MATCH_INDEX = 0;

const int NEXT_CHAR_ADJUSTMENT = 1;

const unsigned int MAXIMUM_NUM_REQUIRED_TIME = 2;

const int INDEX_FIRST_ELEMENT = 0;

//The escape character provided to resolve potential misinterpretation is backslash
const char ESCAPE_CHARACTER = '\\';

const int SIZE_REQUIRED_TO_SORT = 2;

const string LOG_PARSETIME = "parseTime is called, received ";
const string LOG_RETRIEVETIME = "retrieveTime is called";
const string LOG_RETRIEVEUNUSEDCONTENT = "retrieveUnusedContent is called, returned ";

THTimeParser::THTimeParser() {
}

void THTimeParser::parseTime(string inputString) {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PARSETIME + inputString);
	Logging.saveLog();

	_timeIndex.clear();
	_timeStorage.clear();
	_originalTimeStorage.clear();
	_inputString = inputString;

	extractTime();
	determineTime();
	extractUnusedContent();
}

void THTimeParser::retrieveTime(vector<string>& destinationStorage) {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_RETRIEVETIME);
	Logging.saveLog();

	for(unsigned int i = 0; i != _timeStorage.size(); i++) {
		destinationStorage.push_back(_timeStorage[i]);
	}
}

string THTimeParser::retrieveUnusedContent() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_RETRIEVEUNUSEDCONTENT + _unusedContent);
	Logging.saveLog();

	return _unusedContent;
}

//extractTime will continuously attempt to parse a string using the same format until no match can be found.
//The order of the format used for parsing follows the precedence rule.
void THTimeParser::extractTime() {
	string contentAfterParsing = _inputString;

	while(parseMeridiemFormat(contentAfterParsing)) {
	}

	while(parse24HFormat(contentAfterParsing)) {
	}
}

//parseMeridiemFormat will attempt to find a match within the string.
//When a match is found, the time will be converted to HHMM format.
bool THTimeParser::parseMeridiemFormat(string& inputString) {
	smatch matchDetails;

	bool isFound = regex_search(inputString, matchDetails, timeMeridiemFormat);

	if(isFound) {
		char charBeforeMatch = matchDetails.prefix().str().back();

		if(isNotEscapeCharacter(charBeforeMatch)) {
			int lastMatchIndex = determineLastMatchIndex();
			unsigned int timeFoundIndex = _inputString.find(matchDetails[MATCH_INDEX], lastMatchIndex + NEXT_CHAR_ADJUSTMENT);
			
			string timeStandardFormat;

			if(isValidMeridiemFormat(matchDetails[MERIDIEM_HOUR_INDEX], matchDetails[MERIDIEM_MINUTE_INDEX], matchDetails[MERIDIEM_AMPM_INDEX], timeStandardFormat)) {
				_timeIndex.push_back(timeFoundIndex);
				_timeStorage.push_back(timeStandardFormat);
				_originalTimeStorage.push_back(matchDetails[MATCH_INDEX]);

				inputString = matchDetails.prefix().str() + matchDetails.suffix().str();
			} else {
				string contentAfterMatch = matchDetails.suffix().str();
				isFound = parseMeridiemFormat(contentAfterMatch);

				if(isFound) {
					inputString = matchDetails.prefix().str() + contentAfterMatch;
				}
			}
		} else {
			string contentAfterMatch = matchDetails.suffix().str();
			isFound = parseMeridiemFormat(contentAfterMatch);

			if(isFound) {
				inputString = matchDetails.prefix().str() + contentAfterMatch;
			}
		}
	}

	return isFound;
}

//parseMeridiemFormat will attempt to find a match within the string.
//When a match is found, the time will be converted to HHMM format.
bool THTimeParser::parse24HFormat(string& inputString) {
	smatch matchDetails;

	bool isFound = regex_search(inputString, matchDetails, time24HFormat);

	if(isFound) {
		char charBeforeMatch = matchDetails.prefix().str().back();

		if(isNotEscapeCharacter(charBeforeMatch)) {
			int lastMatchIndex = determineLastMatchIndex();
			unsigned int timeFoundIndex = _inputString.find(matchDetails[MATCH_INDEX], lastMatchIndex + NEXT_CHAR_ADJUSTMENT);
			
			string timeStandardFormat = matchDetails[DIGIT_24H_HOUR_INDEX].str() + matchDetails[DIGIT_24H_MINUTE_INDEX].str();

			_timeIndex.push_back(timeFoundIndex);
			_timeStorage.push_back(timeStandardFormat);
			_originalTimeStorage.push_back(matchDetails[MATCH_INDEX]);

			inputString = matchDetails.prefix().str() + matchDetails.suffix().str();
		} else {
			string contentAfterMatch = matchDetails.suffix().str();
			isFound = parse24HFormat(contentAfterMatch);

			if(isFound) {
				inputString = matchDetails.prefix().str() + contentAfterMatch;
			}
		}
	}

	return isFound;
}

int THTimeParser::determineLastMatchIndex() {
	int lastMatchIndex;

	if(!_timeIndex.empty()) {
		lastMatchIndex = _timeIndex.back();
	} else {
		lastMatchIndex = DEFAULT_LAST_MATCH_INDEX;
	}

	return lastMatchIndex;
}

bool THTimeParser::isValidMeridiemFormat(string hourString, string minuteString, string AMPMString, string& timeStandardFormat) {
	bool isValidStatus = false;

	if(isAnteMeridiem(AMPMString)) {
		timeStandardFormat = composeAnteMeridiem(hourString, minuteString);
		isValidStatus = true;
	}

	if(isPostMeridiem(AMPMString)) {		
		timeStandardFormat = composePostMeridiem(hourString, minuteString);
		isValidStatus = true;
	}

	if(isMidnightMeridiem(hourString, AMPMString)) {
		timeStandardFormat = composeMidnightMeridiem(minuteString);
		isValidStatus = true;
	}

	if(isNoonMeridiem(hourString, AMPMString)) {
		timeStandardFormat = composeNoonMeridiem(minuteString);
		isValidStatus = true;
	}

	return isValidStatus;
}

bool THTimeParser::isAnteMeridiem(string AMPMString) {
	toUpperCase(AMPMString);

	return (AMPMString == ANTE_MERIDIEM);
}

bool THTimeParser::isPostMeridiem(string AMPMString) {
	toUpperCase(AMPMString);

	return (AMPMString == POST_MERIDIEM);
}

bool THTimeParser::isMidnightMeridiem(string hourString, string AMPMString) {
	toUpperCase(AMPMString);

	return (hourString == MIDNIGHT_MERIDIEM_HOUR) && (AMPMString == MIDNIGHT_MERIDIEM);
}

bool THTimeParser::isNoonMeridiem(string hourString, string AMPMString) {
	toUpperCase(AMPMString);

	return (hourString == NOON_MERIDIEM_HOUR) && (AMPMString == NOON_MERIDIEM);
}

string THTimeParser::composeAnteMeridiem(string hourString, string minuteString) {
	int hourInt = stringToInt(hourString) % MIDNIGHT_TO_ZERO_ADJUSTMENT;
	hourString = intToString(hourInt);

	while(hourString.size() < STANDARD_HOUR_SIZE) {
		hourString = STANDARD_HOUR_SIZE_ADJUSTMENT + hourString;
	}

	while(minuteString.size() < STANDARD_MINUTE_SIZE) {
		minuteString = STANDARD_MINUTE_SIZE_ADJUSTMENT + minuteString;
	}

	return hourString + minuteString;
}

string THTimeParser::composePostMeridiem(string hourString, string minuteString) {
	int hourInt = (stringToInt(hourString) + POST_MERIDIEM_TO_DIGIT_ADJUSTMENT) % NUMBER_HOURS_IN_DAY;
	
	if(hourInt == MIDNIGHT_HOUR_INT) {
		hourInt = hourInt + POST_MERIDIEM_TO_DIGIT_ADJUSTMENT;
	}

	hourString = intToString(hourInt);

	while(hourString.size() < STANDARD_HOUR_SIZE) {
		hourString = STANDARD_HOUR_SIZE_ADJUSTMENT + hourString;
	}

	while(minuteString.size() < STANDARD_MINUTE_SIZE) {
		minuteString = STANDARD_MINUTE_SIZE_ADJUSTMENT + minuteString;
	}

	return hourString + minuteString;
}

string THTimeParser::composeMidnightMeridiem(string minuteString) {
	if(minuteString.empty()) {
		minuteString = MIDNIGHT_DIGIT_MINUTE;
	}
	return MIDNIGHT_DIGIT_HOUR + minuteString;
}

string THTimeParser::composeNoonMeridiem(string minuteString) {
	if(minuteString.empty()) {
		minuteString = NOON_DIGIT_MINUTE;
	}
	return NOON_DIGIT_HOUR + minuteString;
}

void THTimeParser::determineTime() {
	if(!_timeStorage.empty()) {

		retainTwoImportantTime();

		if(_timeStorage.size() == MAXIMUM_NUM_REQUIRED_TIME) { 
			sortTimeByAppearance();
		}
	}
}

void THTimeParser::retainTwoImportantTime() {
	unsigned int earliestTimeIndex;

	while(_timeStorage.size() > MAXIMUM_NUM_REQUIRED_TIME) {
		earliestTimeIndex = INDEX_FIRST_ELEMENT;

		for(unsigned int i = 0; i != _timeIndex.size(); i++) {
			if(_timeIndex[earliestTimeIndex] > _timeIndex[i]) {
				earliestTimeIndex = i;
			}
		}

		_timeIndex.erase(_timeIndex.begin() + earliestTimeIndex);
		_timeStorage.erase(_timeStorage.begin() + earliestTimeIndex);
		_originalTimeStorage.erase(_originalTimeStorage.begin() + earliestTimeIndex);
	}
}

//time which appeared later will be stored in lower index
void THTimeParser::sortTimeByAppearance() {
	assert(_timeIndex.size() == SIZE_REQUIRED_TO_SORT);
	assert(_timeStorage.size() == SIZE_REQUIRED_TO_SORT);
	assert(_originalTimeStorage.size() == SIZE_REQUIRED_TO_SORT);

	if(_timeIndex[FIRST_TIME_INDEX] < _timeIndex[SECOND_TIME_INDEX]) {
		int tempIndex;
		string tempTime;
		string tempOriginalTime;

		tempIndex = _timeIndex[FIRST_TIME_INDEX];
		_timeIndex[FIRST_TIME_INDEX] = _timeIndex[SECOND_TIME_INDEX];
		_timeIndex[SECOND_TIME_INDEX] = tempIndex;

		tempTime = _timeStorage[FIRST_TIME_INDEX];
		_timeStorage[FIRST_TIME_INDEX] = _timeStorage[SECOND_TIME_INDEX];
		_timeStorage[SECOND_TIME_INDEX] = tempTime;

		tempOriginalTime = _originalTimeStorage[FIRST_TIME_INDEX];
		_originalTimeStorage[FIRST_TIME_INDEX] = _originalTimeStorage[SECOND_TIME_INDEX];
		_originalTimeStorage[SECOND_TIME_INDEX] = tempOriginalTime;
	}
}

void THTimeParser::extractUnusedContent() {
	_unusedContent = _inputString;

	for(unsigned int i = 0; i != _timeStorage.size(); i++) {
		_unusedContent.erase(_timeIndex[i], _originalTimeStorage[i].size());
	}
}

bool THTimeParser::isNotEscapeCharacter(char checkCharacter) {
	return checkCharacter != ESCAPE_CHARACTER;
}

void THTimeParser::toUpperCase(string& input) {
	transform(input.begin(), input.end(), input.begin(), toupper);
}

int THTimeParser::stringToInt(string inputString) {
	return atoi(inputString.c_str());
}

string THTimeParser::intToString(int inputInt) {
	return to_string(inputInt);
}