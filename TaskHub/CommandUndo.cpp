#include "Logic.h"
#include "CommandUndo.h"


const string undoChange::MESSAGE_COMMAND_UNDO = "%s is undo";
const string undoChange::COMMAND_TYPE_ADD = "add";
const string undoChange::MESSAGE_ERROR = "previous action cannot be redo";
const string undoChange::COMMAND_TYPE_UPDATE = "update";
const string undoChange::COMMAND_TYPE_CLEAR = "clear";
const string undoChange::COMMAND_TYPE_DONE = "done";
const string undoChange::COMMAND_TYPE_UNCOMPLETE = "uncomplete";
const string undoChange::COMMAND_TYPE_DELETE = "delete";

undoChange::undoChange () {

}

undoChange::~undoChange () {

}

string undoChange::undo() {

	vector<Task> temporary = Logic::history.getVectorTextStorage();

	if (Logic::history.getLastCommandType() == COMMAND_TYPE_ADD) {
		//temporary=Logic::history.getBackUpStorage();
		temporary.pop_back();
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_ADD.c_str());
		
	}

	else if (Logic::history.getLastCommandType() == COMMAND_TYPE_UPDATE) {
		temporary[Logic::history.getLastChangedTaskIndex()] = Logic::history.getLastUnchangedTask();
		
		Logic::history.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_UPDATE.c_str());
		
	} 
	else if (Logic::history.getLastCommandType() == COMMAND_TYPE_CLEAR) {
		temporary=Logic::history.getBackUpStorage();
		Logic::history.setVectorTextStorage(temporary);
	
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_CLEAR.c_str());
		
	}
	else if (Logic::history.getLastCommandType() == COMMAND_TYPE_DELETE) {
		
		temporary.insert(temporary.begin() + Logic::history.getLastChangedTaskIndex(), Logic::history.getLastUnchangedTask());
		Logic::history.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_DELETE.c_str());
		
	}
	else if (Logic::history.getLastCommandType() == COMMAND_TYPE_UNCOMPLETE) {
		temporary[Logic::history.getLastChangedTaskIndex()].MarkUndone();
		Logic::history.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_UNCOMPLETE.c_str());
		
	}
	else if (Logic::history.getLastCommandType() == COMMAND_TYPE_DONE) {
		temporary[Logic::history.getLastChangedTaskIndex()].MarkUndone();
		Logic::history.setVectorTextStorage(temporary);
	
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_DONE.c_str());
		
	}
	else{
		sprintf_s(Logic::messageDisplayed,MESSAGE_ERROR.c_str());
		
	}
	return Logic::messageDisplayed;
}

