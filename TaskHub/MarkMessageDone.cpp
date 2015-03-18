#include "Logic.h"
#include "MarkMessageDone.h"

const string markingDoneMessage::MESSAGE_COMMAND_TYPE="done";

string markingDoneMessage::markMessageDone(string input) {

	int index;
	istringstream in(input);
	in >> index;

	Logic::lastCommandType = "done";
	Logic::lastChangedTaskIndex = index-1;

	Logic::textStorage[index-1].MarkDone();
	string output = "Task " + input + " marked as done";
	return output;

}

