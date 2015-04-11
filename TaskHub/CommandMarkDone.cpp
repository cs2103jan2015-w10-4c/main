#include "LogicController.h"
#include "CommandMarkDone.h"

const string markingDoneMessage::MESSAGE_COMMAND_TYPE = "done";
const string markingDoneMessage::MESSAGE_MARK_DONE = "Task \" %s \" is completed";
const string markingDoneMessage::MESSAGE_INVALID_INDEX = "Invalid index";

markingDoneMessage::markingDoneMessage () {

}

markingDoneMessage::~markingDoneMessage () {

}

string markingDoneMessage::markMessageDone(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;
	
	if (index > 0 && index <= StorageDatabase::taskHistory.getVectorTextStorage().size()) {
		StorageDatabase::taskHistory.setLastCommandType(MESSAGE_COMMAND_TYPE);
		StorageDatabase::taskHistory.setLastChangedTaskIndex (index);

		vector<Task> temporary = StorageDatabase::taskHistory.getVectorTextStorage();
		temporary[index - 1].MarkDone();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		Task taskMarked = temporary[index - 1];
		
		sprintf_s(Logic::messageDisplayed,MESSAGE_MARK_DONE.c_str(),taskMarked.ToString().c_str());

	} else {
		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
	}

	return Logic::messageDisplayed;

}

