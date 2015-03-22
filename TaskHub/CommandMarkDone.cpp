#include "Logic.h"
#include "CommandMarkDone.h"

const string markingDoneMessage::MESSAGE_COMMAND_TYPE="done";

string markingDoneMessage::markMessageDone(string input) {

	int index;
	istringstream in(input);
	in >> index;

	Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
	Logic::history.setLastChangedTaskIndex (index);

	Logic::history.getVectorTextStorage()[index-1].MarkDone();
	string output = "Task " + input + " marked as done";
	return output;

}

