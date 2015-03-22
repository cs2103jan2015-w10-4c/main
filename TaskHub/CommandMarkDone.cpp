#include "Logic.h"
#include "CommandMarkDone.h"

const string markingDoneMessage::MESSAGE_COMMAND_TYPE="done";

string markingDoneMessage::markMessageDone(string input) {

	int index;
	istringstream in(input);
	in >> index;

	Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
	Logic::history.setLastChangedTaskIndex (index);

	vector<Task> temporary=Logic::history.getVectorTextStorage();
	temporary[index-1].MarkDone();
	Logic::history.setVectorTextStorage(temporary);
	string output = "Task " + input + " marked as done";
	return output;

}

