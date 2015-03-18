#include "Logic.h"
#include "Parser.h"
#include "CommandAdd.h"

const string CommandAdd::MESSAGE_COMMAND_TYPE= "add";
const string CommandAdd::MESSAGE_ADDED="Task added";

string CommandAdd::addMessage(string input) {

	Logic::lastCommandType = MESSAGE_COMMAND_TYPE;

	Task newTask(input);
	Logic::textStorage.push_back(newTask);
	string output = MESSAGE_ADDED;

	Logic::lastChangedTask = newTask;

	return output;

}