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
	assert(index > 0 && index <= Logic::history.getVectorTextStorage().size());

	//Exception
	//if (index <= 0){
	//	throw std::string("Error: Invalid index input");
	//}

	//string output;
	//if (index > Logic::textStorage.size() || index <= 0){
	//	output = "Task " + input + " does not exit";
	//}
	//else{        
		Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
		Logic::history.setLastChangedTaskIndex(index);
		Logic::history.setLastUnchangedTask (Logic::history.getVectorTextStorage()[index - 1]);
		vector<Task> temporary=Logic::history.getVectorTextStorage();
		temporary.erase(temporary.begin() + index - 1);
		Logic::history.setVectorTextStorage(temporary);
		string output = "Task " + input + " deleted";
		
	//}

	return output;
}