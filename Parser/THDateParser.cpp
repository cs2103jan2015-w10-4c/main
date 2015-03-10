#include "THDateParser.h"
#include <string>
#include <vector>
#include <regex>
#include <cassert>
#include "THInputDateCheck.h"
#include "THLogging.h"

using namespace std;

//word format refers to dates which have the month written in word form
//For example, November, nov. The match will be case-insensitive
//digit format refers to dates with month written in digits.
//Back reference is used in this case, meaning 23.11/2014 will be rejected
const regex wordFormatWithYear("\\b((?:\\d)?\\d)([-/.\\s])?(Jan(?:uary)?|Feb(?:ruary)?|Mar(?:ch)?|Apr(?:il)?|May|Jun(?:e)?|Jul(?:y)?|Aug(?:ust)?|Sep(?:tember)?|Oct(?:ober)?|Nov(?:ember)?|Dec(?:ember)?)\\2(\\d\\d\\d\\d)\\b", regex_constants::icase);
const regex wordFormatWithoutYear("\\b((?:\\d)?\\d)([-/.\\s])?(Jan(?:uary)?|Feb(?:ruary)?|Mar(?:ch)?|Apr(?:il)?|May|Jun(?:e)?|Jul(?:y)?|Aug(?:ust)?|Sep(?:tember)?|Oct(?:ober)?|Nov(?:ember)?|Dec(?:ember)?)\\b", regex_constants::icase);
const regex digitFormatWithYear("\\b((?:\\d)?\\d)([-/.])((?:\\d)?\\d)\\2(\\d\\d\\d\\d)\\b");
const regex digitFormatWithoutYear("\\b((?:\\d)?\\d)([-/.])((?:\\d)?\\d)\\b");

//These indexes are used to locate information stored within the smatch
const unsigned int MATCH_INDEX = 0;
const unsigned int DAY_INDEX = 1;
const unsigned int MONTH_INDEX = 3;
const unsigned int YEAR_INDEX = 4;

const unsigned int FIRST_DATE_INDEX = 0;
const unsigned int SECOND_DATE_INDEX = 1;

const int DEFAULT_FIRST_MATCH_INDEX = 0;
const int DEFAULT_LAST_MATCH_INDEX = 0;

const int NEXT_CHAR_ADJUSTMENT = 1;

const unsigned int MIN_SIZE_DATE_WITH_YEAR = 7;
const unsigned int MAXIMUM_NUM_REQUIRED_DATES = 2;

//The escape character provided to resolve misinterpretation is backslash
const char ESCAPE_CHARACTER = '\\';

const int SIZE_REQUIRED_TO_SORT = 2;

const string LOG_PARSEDATE = "parseDate is called, received ";
const string LOG_RETRIEVEDATE = "retrieveDate is called";
const string LOG_RETRIEVEUNUSEDCONTENT = "retrieveUnusedContent is called, returned ";

THDateParser::THDateParser() {
}

void THDateParser::parseDate(string inputString) {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_PARSEDATE + inputString);
	Logging.saveLog();

	_dateIndex.clear();
	_dateStorage.clear();
	_originalDateStorage.clear();
	_inputString = inputString;
	_higherPriorityAdjustment = _inputString.size();

	extractDate();
	determineDate();
	extractUnusedContent();
}

void THDateParser::retrieveDate(vector<string>& destinationStorage) {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_RETRIEVEDATE);
	Logging.saveLog();

	for(unsigned int i = 0; i != _dateStorage.size(); i++) {
		destinationStorage.push_back(_dateStorage[i]);
	}
}

string THDateParser::retrieveUnusedContent() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_RETRIEVEUNUSEDCONTENT + _unusedContent);
	Logging.saveLog();

	return _unusedContent;
}

//extractDate will continuously attempt to parse a string using the same format until no match can be found.
//The order of the format used for parsing follows the precedence rule.
void THDateParser::extractDate() {
	string contentAfterParsing = _inputString;

	while(parseWordFormatWithYear(contentAfterParsing)) {
	}

	while(parseDigitFormatWithYear(contentAfterParsing)) {
	}

	while(parseWordFormatWithoutYear(contentAfterParsing)) {
	}

	while(parseDigitFormatWithoutYear(contentAfterParsing)) {
	}
}

//parseWordFormatWithYear will attempt to find a match within the string.
//When a match is found, the date will be converted to YYYYMMDD format.
//The date will also be checked for validity using THInputDateCheck
bool THDateParser::parseWordFormatWithYear(string& inputString) {
	smatch matchDetails;

	bool isFound = regex_search(inputString, matchDetails, wordFormatWithYear);

	if(isFound) {
		char charBeforeMatch = matchDetails.prefix().str().back();
		
		if(isNotEscapeCharacter(charBeforeMatch)) {
			int lastMatchIndex = determineLastMatchIndex();
			unsigned int dateFoundIndex = _inputString.find(matchDetails[MATCH_INDEX], lastMatchIndex + NEXT_CHAR_ADJUSTMENT);
			
			string dateStandardFormat;

			if(_dateChecker.isValidDateWordFormat(matchDetails[YEAR_INDEX], matchDetails[MONTH_INDEX], matchDetails[DAY_INDEX], dateStandardFormat)) {
				_dateIndex.push_back(dateFoundIndex);
				_dateStorage.push_back(dateStandardFormat);
				_originalDateStorage.push_back(matchDetails[MATCH_INDEX]);

				inputString = matchDetails.prefix().str() + matchDetails.suffix().str();
			} else {
				string contentAfterMatch = matchDetails.suffix().str();
				isFound = parseWordFormatWithYear(contentAfterMatch);

				if(isFound) {
					inputString = matchDetails.prefix().str() + contentAfterMatch;
				}
			}
		} else {
			string contentAfterMatch = matchDetails.suffix().str();
			isFound = parseWordFormatWithYear(contentAfterMatch);

			if(isFound) {
				inputString = matchDetails.prefix().str() + contentAfterMatch;
			}
		}
	}

	return isFound;
}

//parseDigitFormatWithYear will attempt to find a match within the string.
//When a match is found, the date will be converted to YYYYMMDD format.
//The date will also be checked for validity using THInputDateCheck
bool THDateParser::parseDigitFormatWithYear(string& inputString) {
	smatch matchDetails;

	bool isFound = regex_search(inputString, matchDetails, digitFormatWithYear);

	if(isFound) {
		char charBeforeMatch = matchDetails.prefix().str().back();

		if(isNotEscapeCharacter(charBeforeMatch)) {
			int lastMatchIndex = determineLastMatchIndex();
			unsigned int dateFoundIndex = _inputString.find(matchDetails[MATCH_INDEX], lastMatchIndex + NEXT_CHAR_ADJUSTMENT);

			string dateStandardFormat;

			if(_dateChecker.isValidDateDigitFormat(matchDetails[YEAR_INDEX], matchDetails[MONTH_INDEX], matchDetails[DAY_INDEX], dateStandardFormat)) {
				_dateIndex.push_back(dateFoundIndex);
				_dateStorage.push_back(dateStandardFormat);
				_originalDateStorage.push_back(matchDetails[MATCH_INDEX]);

				inputString = matchDetails.prefix().str() + matchDetails.suffix().str();
			} else {
				string contentAfterMatch = matchDetails.suffix().str();
				isFound = parseDigitFormatWithYear(contentAfterMatch);

				if(isFound) {
					inputString = matchDetails.prefix().str() + contentAfterMatch;
				}
			}
		} else {
			string contentAfterMatch = matchDetails.suffix().str();
			isFound = parseDigitFormatWithYear(contentAfterMatch);

			if(isFound) {
				inputString = matchDetails.prefix().str() + contentAfterMatch;
			}
		}
	}

	return isFound;
}

//parseWordFormatWithoutYear will attempt to find a match within the string.
//When a match is found, the date will be converted to YYYYMMDD format.
//The year will be taken as the nearest year without the date being overdue
//The date will also be checked for validity using THInputDateCheck
bool THDateParser::parseWordFormatWithoutYear(string& inputString) {
	smatch matchDetails;

	bool isFound = regex_search(inputString, matchDetails, wordFormatWithoutYear);

	if(isFound) {
		char charBeforeMatch = matchDetails.prefix().str().back();

		if(isNotEscapeCharacter(charBeforeMatch)) {
			int lastMatchIndex = determineLastMatchIndex();
			unsigned int dateFoundIndex = _inputString.find(matchDetails[MATCH_INDEX], lastMatchIndex + NEXT_CHAR_ADJUSTMENT);

			string dateStandardFormat;

			if(_dateChecker.isValidDateWordFormatWithoutYear(matchDetails[MONTH_INDEX], matchDetails[DAY_INDEX], dateStandardFormat)) {
				_dateIndex.push_back(dateFoundIndex);
				_dateStorage.push_back(dateStandardFormat);
				_originalDateStorage.push_back(matchDetails[MATCH_INDEX]);

				inputString = matchDetails.prefix().str() + matchDetails.suffix().str();
			} else {
				string contentAfterMatch = matchDetails.suffix().str();
				isFound = parseWordFormatWithoutYear(contentAfterMatch);

				if(isFound) {
					inputString = matchDetails.prefix().str() + contentAfterMatch;
				}
			}
		} else {
			string contentAfterMatch = matchDetails.suffix().str();
			isFound = parseWordFormatWithoutYear(contentAfterMatch);

			if(isFound) {
				inputString = matchDetails.prefix().str() + contentAfterMatch;
			}
		}
	}

	return isFound;
}

//parseDigitFormatWithoutYear will attempt to find a match within the string.
//When a match is found, the date will be converted to YYYYMMDD format.
//The year will be taken as the nearest year without the date being overdue
//The date will also be checked for validity using THInputDateCheck
bool THDateParser::parseDigitFormatWithoutYear(string& inputString) {
	smatch matchDetails;

	bool isFound = regex_search(inputString, matchDetails, digitFormatWithoutYear);

	if(isFound) {
		char charBeforeMatch = matchDetails.prefix().str().back();

		if(isNotEscapeCharacter(charBeforeMatch)) {
			int lastMatchIndex = determineLastMatchIndex();
			unsigned int dateFoundIndex = _inputString.find(matchDetails[MATCH_INDEX], lastMatchIndex + NEXT_CHAR_ADJUSTMENT);

			string dateStandardFormat;

			if(_dateChecker.isValidDateDigitFormatWithoutYear(matchDetails[MONTH_INDEX], matchDetails[DAY_INDEX], dateStandardFormat)) {
				_dateIndex.push_back(dateFoundIndex);
				_dateStorage.push_back(dateStandardFormat);
				_originalDateStorage.push_back(matchDetails[MATCH_INDEX]);

				inputString = matchDetails.prefix().str() + matchDetails.suffix().str();
			} else {
				string contentAfterMatch = matchDetails.suffix().str();
				isFound = parseDigitFormatWithoutYear(contentAfterMatch);

				if(isFound) {
					inputString = matchDetails.prefix().str() + contentAfterMatch;
				}
			}
		} else {
			string contentAfterMatch = matchDetails.suffix().str();
			isFound = parseDigitFormatWithoutYear(contentAfterMatch);

			if(isFound) {
				inputString = matchDetails.prefix().str() + contentAfterMatch;
			}
		}
	}

	return isFound;
}

int THDateParser::determineLastMatchIndex() {
	int lastMatchIndex;

	if(!_dateIndex.empty()) {
		lastMatchIndex = _dateIndex.back();
	} else {
		lastMatchIndex = DEFAULT_LAST_MATCH_INDEX;
	}

	return lastMatchIndex;
}

void THDateParser::determineDate() {
	if(!_dateStorage.empty()) {
		allocatePriority();
		retainTwoImportantDates();
		deallocatePriority();

		if(_dateStorage.size() == MAXIMUM_NUM_REQUIRED_DATES) {
			sortDatesByAppearance();
		}
	}
}

void THDateParser::retainTwoImportantDates() {
	unsigned int earliestDateIndex;

	while(_dateStorage.size() > MAXIMUM_NUM_REQUIRED_DATES) {
		earliestDateIndex = DEFAULT_FIRST_MATCH_INDEX;

		for(unsigned int i = 0; i != _dateIndex.size(); i++) {
			if(_dateIndex[earliestDateIndex] > _dateIndex[i]) {
				earliestDateIndex = i;
			}
		}

		if(_dateIndex[earliestDateIndex] > _inputString.size()) {
			_dateIndex[earliestDateIndex] = _dateIndex[earliestDateIndex] - _higherPriorityAdjustment;
		}

		_dateIndex.erase(_dateIndex.begin() + earliestDateIndex);
		_dateStorage.erase(_dateStorage.begin() + earliestDateIndex);
		_originalDateStorage.erase(_originalDateStorage.begin() + earliestDateIndex);
	}
}

void THDateParser::allocatePriority() {
	for(unsigned int i = 0; i != _dateStorage.size(); i++) {
		if(_originalDateStorage[i].size() >= MIN_SIZE_DATE_WITH_YEAR) {
			_dateIndex[i] = _dateIndex[i] + _higherPriorityAdjustment;
		}
	}
}

void THDateParser::deallocatePriority() {
	for(unsigned int i = 0; i != _dateStorage.size(); i++) {
		if(_dateIndex[i] > _inputString.size()) {
			_dateIndex[i] = _dateIndex[i] - _higherPriorityAdjustment;
		}
	}
}

//dates which appeared later will be stored in lower index
void THDateParser::sortDatesByAppearance() {
	assert(_dateIndex.size() == SIZE_REQUIRED_TO_SORT);
	assert(_dateStorage.size() == SIZE_REQUIRED_TO_SORT);
	assert(_originalDateStorage.size() == SIZE_REQUIRED_TO_SORT);

	if(_dateIndex[FIRST_DATE_INDEX] < _dateIndex[SECOND_DATE_INDEX]) {
		int tempIndex;
		string tempDate;
		string tempOriginalDate;

		tempIndex = _dateIndex[FIRST_DATE_INDEX];
		_dateIndex[FIRST_DATE_INDEX] = _dateIndex[SECOND_DATE_INDEX];
		_dateIndex[SECOND_DATE_INDEX] = tempIndex;

		tempDate = _dateStorage[FIRST_DATE_INDEX];
		_dateStorage[FIRST_DATE_INDEX] = _dateStorage[SECOND_DATE_INDEX];
		_dateStorage[SECOND_DATE_INDEX] = tempDate;

		tempOriginalDate = _originalDateStorage[FIRST_DATE_INDEX];
		_originalDateStorage[FIRST_DATE_INDEX] = _originalDateStorage[SECOND_DATE_INDEX];
		_originalDateStorage[SECOND_DATE_INDEX] = tempOriginalDate;
	}
}

void THDateParser::extractUnusedContent() {
	_unusedContent = _inputString;

	for(unsigned int i = 0; i != _dateStorage.size(); i++) {
		if(_dateIndex[i] > _inputString.size()) {
			_dateIndex[i] = _dateIndex[i] - _higherPriorityAdjustment;
		}

		_unusedContent.erase(_dateIndex[i], _originalDateStorage[i].size());
	}
}

bool THDateParser::isNotEscapeCharacter(char checkCharacter) {
	return checkCharacter != ESCAPE_CHARACTER;
}
