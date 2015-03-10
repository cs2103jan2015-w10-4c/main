#include "THCommand.h"
using namespace std;

void THCommand::clearCommand() {
	_commandType = THUtility::INVALID;
	_description = "";
	_StartingDate = "";
	_StartingTime = "";
	_EndingDate = "";
	_EndingTime = "";
	_haveCommand = false;
}

THCommand::THCommand() {
	_haveCommand = false;
}

void THCommand::setCommand (THUtility::CommandType userCommand) {
	_commandType=userCommand;
	_haveCommand=true;
}

void THCommand::setDescription (string userMessage) {
	_description=userMessage;
}

bool THCommand::haveStartingDate() {
	return (!_StartingDate.empty());
}

bool THCommand::haveStartingTime() {
	return (!_StartingTime.empty());
}

bool THCommand::haveEndingDate() {
	return (!_EndingDate.empty());
}

bool THCommand::haveEndingTime() {
	return (!_EndingTime.empty());
}

THUtility::CommandType THCommand::getCommand() {
	return _commandType;
}

string THCommand::getDescription() {
	return _description;
}

string THCommand::getStartingDate() {
	return _StartingDate;
}

string THCommand::getStartingTime() {
	return _StartingTime;
}

string THCommand::getEndingDate() {
	return _EndingDate;
}

string THCommand::getEndingTime() {
	return _EndingTime;
}

void THCommand::clearCommand() {
	_commandType = THUtility::INVALID;
	_description = "";
	_StartingDate = "";
	_StartingTime = "";
	_EndingDate = "";
	_EndingTime = "";
	_haveCommand = false;
}