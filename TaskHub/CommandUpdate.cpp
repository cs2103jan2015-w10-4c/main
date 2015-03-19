#include "CommandUpdate.h"
#include "Logic.h"
#include "Parser.h"

const string UpdatingMessage::MESSAGE_COMMAND_TYPE="update";

string UpdatingMessage::updateMessage(string input) {

	string TaskIndex = Logic::getFirstWord(input);
	string TaskInfo = Logic::removeFirstWord(input);

	unsigned int index;
	istringstream in(TaskIndex);
	in >> index;

	string output;
	if (index > Logic::textStorage.size() || index <= 0){
		output = "Task " + TaskIndex + " does not exit";
		
	}
	else{
		Logic::lastCommandType = MESSAGE_COMMAND_TYPE;
		Logic::lastChangedTaskIndex = index - 1;
		Logic::lastUnchangedTask = Logic::textStorage[index - 1];

		Logic::textStorage[index-1].UpdateTask(TaskInfo);

		Logic::lastChangedTask = Logic::textStorage[index - 1];

		output = "Task " + TaskIndex + " updated";
		
	}

	return output;
}