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
	if (index > Logic::history.getVectorTextStorage().size() || index <= 0){
		output = "Task " + TaskIndex + " does not exit";
		
	}
	else{
		Logic::history.setLastCommandType(MESSAGE_COMMAND_TYPE);
		Logic::history.setLastChangedTaskIndex ( index - 1);
		vector<Task> temp=Logic::history.getVectorTextStorage();

		Logic::history.setLastUnchangedTask (temp[index - 1]);

		temp[index -1].UpdateTask(TaskInfo);

		Logic::history.setLastChangedTask(temp[index - 1]);

		Logic::history.setVectorTextStorage(temp);

		output = "Task " + TaskIndex + " updated";
		
	}

	return output;
}