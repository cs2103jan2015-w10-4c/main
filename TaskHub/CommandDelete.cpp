#include "Logic.h"
#include "Parser.h"
#include "CommandDelete.h"


const string CommandDelete::MESSAGE_COMMAND_TYPE="delete";
const string CommandDelete::MESSAGE_DELETED="Message \" %s \" is deleted";
const string CommandDelete::MESSAGE_INVALID_INDEX="Invalid index";

string CommandDelete::deleteMessage(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;
	
	if (index > 0 && index <= Logic::history.getVectorTextStorage().size()) {
      
		Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
		Logic::history.setLastChangedTaskIndex(index);
		Logic::history.setLastUnchangedTask (Logic::history.getVectorTextStorage()[index - 1]);
		
		vector<Task> temporary=Logic::history.getVectorTextStorage();
		Task taskDeleted=temporary[index-1];
		temporary.erase(temporary.begin() + index - 1);
		Logic::history.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed,MESSAGE_DELETED.c_str(), taskDeleted.ToString().c_str());

	} else {
		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
	}
		return Logic::messageDisplayed;
}