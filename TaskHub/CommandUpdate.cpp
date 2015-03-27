#include "CommandUpdate.h"
#include "Logic.h"
#include "Parser.h"

const string CommandUpdate::MESSAGE_COMMAND_TYPE="update";
const string CommandUpdate::MESSAGE_INVALID_INDEX="The index is invalid";
const string CommandUpdate::MESSAGE_UPDATED="Task: %s is updated";

string CommandUpdate::updateMessage(string input) {

	string TaskIndex = Logic::getFirstWord(input);
	string TaskInfo = Logic::removeFirstWord(input);

	unsigned int index;
	istringstream in(TaskIndex);
	in >> index;

	if (index > Logic::history.getVectorTextStorage().size() || index <= 0){
		
		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
		
	}
	else{
		Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
		Logic::history.setLastChangedTaskIndex ( index);
		vector<Task> temp=Logic::history.getVectorTextStorage();

		Logic::history.setLastUnchangedTask (temp[index - 1]);

		temp[index -1].UpdateTask(TaskInfo);

		Logic::history.setLastChangedTask(temp[index - 1]);

		Logic::history.setVectorTextStorage(temp);

		sprintf_s(Logic::messageDisplayed,MESSAGE_UPDATED.c_str(),temp[index-1].ToString().c_str());
		
	}

	return Logic::messageDisplayed;
}