#include "Logic.h"
#include "CommandRedo.h"


const string redoChange::MESSAGE_COMMAND_TYPE="redo";

string redoChange::redo() {

	if (Logic::lastCommandType == "add"){
		Logic::textStorage.push_back(Logic::lastChangedTask);
		return "Adding command is redone";
	}
	else if (Logic::lastCommandType == "update"){
		Logic::textStorage[Logic::lastChangedTaskIndex] = Logic::lastChangedTask;
		return "Updating command is redone";
	}
	else if (Logic::lastCommandType == "delete"){
		Logic::textStorage.erase(Logic::textStorage.begin() + Logic::lastChangedTaskIndex);
		return "Deleting command is redone";
	}
	else if (Logic::lastCommandType == "done"){
		Logic::textStorage[Logic::lastChangedTaskIndex].MarkDone();
		return "MarkDone command is redone";
	}
	else{
		return "previous action cannot be redo";
	}

}
