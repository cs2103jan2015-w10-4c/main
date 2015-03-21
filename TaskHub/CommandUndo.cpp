#include "Logic.h"
#include "CommandUndo.h"


const string undoChange::MESSAGE_COMMAND_TYPE="undo";

string undoChange::undo() {

	vector<Task> temporary =Logic::history.getVectorTextStorage();

	if (Logic::history.getLastCommandType() == "add"){
		temporary.pop_back();
		Logic::history.setVectorTextStorage(temporary);
		return "Adding command is undone";
	}
	else if (Logic::history.getLastCommandType() == "update"){
		temporary[Logic::history.getLastChangedTaskIndex()] = Logic::history.getLastUnchangedTask();
		Logic::history.setVectorTextStorage(temporary);
		return "Updating command is undone";
	}
	else if (Logic::history.getLastCommandType() == "delete"){
		
		cout<<"1\n";
		temporary.insert(Logic::history.getVectorTextStorage().begin() + Logic::history.getLastChangedTaskIndex(), Logic::history.getLastUnchangedTask());
		cout<<"2\n";
		Logic::history.setVectorTextStorage(temporary);
		return "Deleting command is undone";
	}
	else if (Logic::history.getLastCommandType() == "done"){
		temporary[Logic::history.getLastChangedTaskIndex()].MarkUndone();
		Logic::history.setVectorTextStorage(temporary);
		return "MarkDone command is undone";
	}
	else{
		return "Previous action cannot be undo";
	}
}
