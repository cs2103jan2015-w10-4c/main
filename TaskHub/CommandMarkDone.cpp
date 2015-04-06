#include "Logic.h"
#include "CommandMarkDone.h"

const string markingDoneMessage::MESSAGE_COMMAND_TYPE = "done";
const string markingDoneMessage::MESSAGE_MARK_DONE = "Task \" %s \" is completed";
const string markingDoneMessage::MESSAGE_INVALID_INDEX = "Invalid index";

string markingDoneMessage::markMessageDone(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;
	
	if (index > 0 && index <= Logic::history.getVectorTextStorage().size()) {
		Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
		Logic::history.setLastChangedTaskIndex (index);

		vector<Task> temporary = Logic::history.getVectorTextStorage();
		temporary[index - 1].MarkDone();
		Logic::history.setVectorTextStorage(temporary);
		Task taskMarked = temporary[index - 1];
		
		sprintf_s(Logic::messageDisplayed,MESSAGE_MARK_DONE.c_str(),taskMarked.ToString().c_str());

	} else {
		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
	}

	return Logic::messageDisplayed;

}

