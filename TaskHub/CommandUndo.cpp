#include "Logic.h"
#include "CommandUndo.h"

const string undoChange::MESSAGE_COMMAND_TYPE="undo";

string undoChange::undo() {

	if (Logic::lastCommandType == "add"){
		Logic::textStorage.pop_back();
		return "Adding command is undone";
	}
	else if (Logic::lastCommandType == "update"){
		Logic::textStorage[Logic::lastChangedTaskIndex] = Logic::lastUnchangedTask;
		return "Updating command is undone";
	}
	else if (Logic::lastCommandType == "delete"){
		Logic::textStorage.insert(Logic::textStorage.begin() + Logic::lastChangedTaskIndex, Logic::lastUnchangedTask);
		return "Deleting command is undone";
	}
	else if (Logic::lastCommandType == "done"){
		Logic::textStorage[Logic::lastChangedTaskIndex].MarkUndone();
		return "MarkDone command is undone";
	}
	else{
		return "Previous action cannot be undo";
	}
}
