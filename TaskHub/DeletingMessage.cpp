#include "Logic.h"
#include "Parser.h"
#include "DeletingMessage.h"

const string deleingMessage::MESSAGE_COMMAND_TYPE="delete";

string deleingMessage::deleteMessage(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;

	string output;
	if (index > Logic::list.size() || index <= 0){
		output = "Textbody " + input + " does not exit";
	}
	else{
		Logic::lastCommandType = MESSAGE_COMMAND_TYPE;
		Logic::lastChangedTextbodyIndex = index-1;
		Logic::lastUnchangedTextbody = Logic::list[index - 1];

		Logic::list.erase(Logic::list.begin() + index - 1);
		string output = "Textbody " + input + " deleted";
		
	}

	return output;
}