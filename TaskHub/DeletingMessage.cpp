#include "Logic.h"
#include "Parser.h"
#include "DeletingMessage.h"
#include <assert.h>							//for assertions

const string deletingMessage::MESSAGE_COMMAND_TYPE="delete";

string deletingMessage::deleteMessage(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;
	//Assertion
	assert(index > 0 && index <= Logic::list.size());

	//Exception
	if (index <= 0){
		throw std::string("Error: Invalid index input");
	}

	//string output;
	//if (index > Logic::list.size() || index <= 0){
	//	output = "Textbody " + input + " does not exit";
	//}
	//else{        
		Logic::lastCommandType = MESSAGE_COMMAND_TYPE;
		Logic::lastChangedTextbodyIndex = index-1;
		Logic::lastUnchangedTextbody = Logic::list[index - 1];

		Logic::list.erase(Logic::list.begin() + index - 1);
		string output = "Textbody " + input + " deleted";
		
	//}

	return output;
}