#include "Logic.h"
#include "Parser.h"
#include "CommandDelete.h"
#include <assert.h>							//for assertions

const string CommandDelete::MESSAGE_COMMAND_TYPE="delete";

string CommandDelete::deleteMessage(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;
	//Assertion
	assert(index > 0 && index <= Logic::textStorage.size());

	//Exception
	if (index <= 0){
		throw std::string("Error: Invalid index input");
	}

	//string output;
	//if (index > Logic::textStorage.size() || index <= 0){
	//	output = "Task " + input + " does not exit";
	//}
	//else{        
		Logic::lastCommandType = MESSAGE_COMMAND_TYPE;
		Logic::lastChangedTaskIndex = index-1;
		Logic::lastUnchangedTask = Logic::textStorage[index - 1];

		Logic::textStorage.erase(Logic::textStorage.begin() + index - 1);
		string output = "Task " + input + " deleted";
		
	//}

	return output;
}