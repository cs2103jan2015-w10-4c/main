#include "THCommandParser.h"
#include <string>
#include "THUtility.h"
using namespace std;

THUtility::CommandType THCommandParser::getCommand(){
	return _commandtype;
}

string THCommandParser::getContent(){
	return _unusedContent;
}

void THCommandParser::determineCommandType(string userInput){
	string userCommand = getFirstWord(userInput);
	if (userCommand == "add"){
		_commandtype = THUtility::ADD;
		_unusedContent = userInput.substr(userCommand.size());
	}
	if (userCommand == "edit"){
		_commandtype = THUtility::EDIT;
		_unusedContent = userInput.substr(userCommand.size());
	}
	if (userCommand == "delete"){
		_commandtype = THUtility::DELETE;
		_unusedContent = userInput.substr(userCommand.size());
	}
	if (userCommand == "search"){
		_commandtype = THUtility::SEARCH;
		_unusedContent = userInput.substr(userCommand.size());
	}
	if (userCommand == "undo"){
		_commandtype = THUtility::UNDO;
		_unusedContent = userInput.substr(userCommand.size());
	}
}

string THCommandParser::getFirstWord(string userInput){
	return userInput.substr(0, userInput.find(' '));
}


