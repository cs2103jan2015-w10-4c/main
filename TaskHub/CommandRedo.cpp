#include "Logic.h"
#include "CommandRedo.h"


const string redoChange::MESSAGE_COMMAND_TYPE="redo";

string redoChange::redo() {

	vector<Task> temporary=Logic::history.getVectorTextStorage();

	if (Logic::history.getLastCommandType() == "add"){
		
		temporary.push_back(Logic::history.getLastChangedTask());
		Logic::history.setVectorTextStorage(temporary);

		return "Adding command is redone";
	}
	else if (Logic::history.getLastCommandType()  == "update"){
		temporary[Logic::history.getLastChangedTaskIndex()] = Logic::history.getLastChangedTask();
		Logic::history.setVectorTextStorage(temporary);
		return "Updating command is redone";
	}
	else if (Logic::history.getLastCommandType()  == "delete"){
		temporary.erase(temporary.begin() + Logic::history.getLastChangedTaskIndex());
		Logic::history.setVectorTextStorage(temporary);
		return "Deleting command is redone";
	}
	else if (Logic::history.getLastCommandType()  == "uncomplete"){
		temporary[Logic::history.getLastChangedTaskIndex()].markUncompleted();
		Logic::history.setVectorTextStorage(temporary);
		return "MarkUncomplete command is redone";
	}
	else if (Logic::history.getLastCommandType()  == "done"){
		temporary[Logic::history.getLastChangedTaskIndex()].MarkDone();
		Logic::history.setVectorTextStorage(temporary);
		return "MarkDone command is redone";
	}
	else{
		return "previous action cannot be redo";
	}

}
