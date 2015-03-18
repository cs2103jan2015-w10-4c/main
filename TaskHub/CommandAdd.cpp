#include "Logic.h"
#include "Parser.h"
#include "CommandAdd.h"

const string CommandAdd::MESSAGE_COMMAND_TYPE= "add";
const string CommandAdd::MESSAGE_ADDED="Textbody added";

string CommandAdd::addMessage(string input) {

	Logic::lastCommandType = MESSAGE_COMMAND_TYPE;

	Textbody newTextbody(input);
	Logic::textStorage.push_back(newTextbody);
	string output = MESSAGE_ADDED;

	Logic::lastChangedTextbody = newTextbody;

	return output;

}