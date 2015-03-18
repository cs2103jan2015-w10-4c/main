#include "UpdatingMessage.h"
#include "Logic.h"
#include "Parser.h"

const string UpdatingMessage::MESSAGE_COMMAND_TYPE="update";

string UpdatingMessage::updateMessage(string input) {

	string TextbodyIndex = Logic::getFirstWord(input);
	string TextbodyInfo = Logic::removeFirstWord(input);

	unsigned int index;
	istringstream in(TextbodyIndex);
	in >> index;

	string output;
	if (index > Logic::textStorage.size() || index <= 0){
		output = "Textbody " + TextbodyIndex + " does not exit";
		
	}
	else{
		Logic::lastCommandType = MESSAGE_COMMAND_TYPE;
		Logic::lastChangedTextbodyIndex = index - 1;
		Logic::lastUnchangedTextbody = Logic::textStorage[index - 1];

		Logic::textStorage[index-1].UpdateTextbody(TextbodyInfo);

		Logic::lastChangedTextbody = Logic::textStorage[index - 1];

		output = "Textbody " + TextbodyIndex + " updated";
		
	}

	return output;
}