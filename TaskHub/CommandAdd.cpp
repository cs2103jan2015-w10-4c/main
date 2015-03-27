#include "Logic.h"
#include "Parser.h"
#include "CommandAdd.h"
#include <algorithm>

const string CommandAdd::MESSAGE_COMMAND_TYPE= "add";
const string CommandAdd::MESSAGE_ADDED="Task: \" %s \" added";
const string CommandAdd::MESSAGE_INDICATING_EMPTY="The input is empty.";

string CommandAdd::addMessage(string input) {

	Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
	bool isWhiteSpace=all_of(input.begin(),input.end(), isspace);

	// this is to make sure if user just key in empty space or nothing except an "add", nothing will be done
	if (!isWhiteSpace && input != "add" ) {
	Task newTask(input);
	Logic::history.setVectorTextStorage(newTask);
	Logic::history.setLastChangedTask(newTask);
	sprintf_s(Logic::messageDisplayed, MESSAGE_ADDED.c_str(),newTask.ToString().c_str());
	

	} else {
		sprintf_s(Logic::messageDisplayed,MESSAGE_INDICATING_EMPTY.c_str());
	}

	return Logic::messageDisplayed;

}