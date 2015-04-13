#include "CommandUpdate.h"
#include "LogicController.h"
#include "Parser.h"

const string CommandUpdate::MESSAGE_COMMAND_TYPE = "update";
const string CommandUpdate::MESSAGE_INVALID_INDEX = "The index is invalid";
const string CommandUpdate::MESSAGE_UPDATED = "Task: %s is updated";

CommandUpdate::CommandUpdate () {

}

CommandUpdate::~CommandUpdate () {

}


bool checkInputValidation(string taskIndex){
	
	bool isValid=true;
	for(unsigned int i=0; i<taskIndex.size()&&isValid;i++){
		if(taskIndex[i]<'0' || taskIndex[i]>'9')
			isValid=false;
	}

	return isValid;
}



string CommandUpdate::updateMessage(string input) {

	string TaskIndex = Logic::getFirstWord(input);
	string TaskInfo = Logic::removeFirstWord(input);

	if (!checkInputValidation(TaskIndex)) {

		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
		return Logic::messageDisplayed;
	}

	unsigned int index;
	istringstream in(TaskIndex);
	in >> index;


	if (index > StorageDatabase::taskHistory.getVectorTextStorage().size() || index <= 0){
		
		sprintf_s(Logic::messageDisplayed,MESSAGE_INVALID_INDEX.c_str());
		
	}
	else{
		StorageDatabase::taskHistory.setLastCommandType(MESSAGE_COMMAND_TYPE);
		StorageDatabase::taskHistory.setLastChangedTaskIndex (index);
		vector<Task> temp = StorageDatabase::taskHistory.getVectorTextStorage();

		StorageDatabase::taskHistory.setLastUnchangedTask (temp[index - 1]);

		temp[index - 1].UpdateTask(TaskInfo);

		StorageDatabase::taskHistory.setLastChangedTask(temp[index - 1]);

		StorageDatabase::taskHistory.setVectorTextStorage(temp);

		sprintf_s(Logic::messageDisplayed,MESSAGE_UPDATED.c_str(),temp[index-1].ToString().c_str());
		
	}

	return Logic::messageDisplayed;
}