//@author A0115365J
#include "LogicController.h"
#include "CommandMarkUncomplete.h"

const string markingMessageUncomplete::MESSAGE_COMMAND_TYPE = "uncomplete";
const string markingMessageUncomplete::MESSAGE_MARK_UNCOMPLETE = "Task \" %s \" is marked";
const string markingMessageUncomplete::MESSAGE_INVALID_INDEX = "Invalid index";

markingMessageUncomplete::markingMessageUncomplete () {

}

markingMessageUncomplete::~markingMessageUncomplete () {

}

//@author A0115365J-reused
string markingMessageUncomplete::markMessageUncompleted(string input) {

	unsigned int index;
	istringstream in(input);
	in >> index;
	
	if (index > 0 && index <= StorageDatabase::taskHistory.getVectorTextStorage().size()) {
		StorageDatabase::taskHistory.setLastCommandType(MESSAGE_COMMAND_TYPE);
		StorageDatabase::taskHistory.setLastChangedTaskIndex (index);

		vector<Task> temporary=StorageDatabase::taskHistory.getVectorTextStorage();
		temporary[index - 1].markUncompleted();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		Task taskMarked = temporary[index - 1];
		
		sprintf_s(Logic::messageDisplayed,MESSAGE_MARK_UNCOMPLETE.c_str(),taskMarked.ToString().c_str());

	} else {
		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
	}

	return Logic::messageDisplayed;

}

