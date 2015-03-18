#include "Logic.h"
#include "Parser.h"
#include "AddingMessage.h"

const string AddingMessage::MESSAGE_COMMAND_TYPE= "add";
const string AddingMessage::MESSAGE_ADDED="Textbody added";

string AddingMessage::addMessage(string input) {

	Logic::lastCommandType = MESSAGE_COMMAND_TYPE;

	Textbody newTextbody(input);
	Logic::textStorage.push_back(newTextbody);
	string output = MESSAGE_ADDED;

	Logic::lastChangedTextbody = newTextbody;

	return output;

}