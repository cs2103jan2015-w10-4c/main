#include "LogicController.h"
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

	vector<Task> temporary = StorageDatabase::taskHistory.getVectorTextStorage();

	if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_ADD) {
		//temporary=StorageDatabase::taskHistory.getBackUpStorage();
		temporary.pop_back();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_ADD.c_str());
		
	}

	else if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_UPDATE) {
		temporary[StorageDatabase::taskHistory.getLastChangedTaskIndex()] = StorageDatabase::taskHistory.getLastUnchangedTask();
		
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_UPDATE.c_str());
		
	} 
	else if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_CLEAR) {
		temporary=StorageDatabase::taskHistory.getBackUpStorage();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
	
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_CLEAR.c_str());
		
	}
	else if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_DELETE) {
		
		temporary.insert(temporary.begin() + StorageDatabase::taskHistory.getLastChangedTaskIndex(), StorageDatabase::taskHistory.getLastUnchangedTask());
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_DELETE.c_str());
		
	}
	else if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_UNCOMPLETE) {
		temporary[StorageDatabase::taskHistory.getLastChangedTaskIndex()].MarkUndone();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_UNCOMPLETE.c_str());
		
	}
	else if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_DONE) {
		temporary[StorageDatabase::taskHistory.getLastChangedTaskIndex()].MarkUndone();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
	
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_UNDO.c_str(), COMMAND_TYPE_DONE.c_str());
		
	}
	else{
		sprintf_s(Logic::messageDisplayed,MESSAGE_ERROR.c_str());
		
	}
	return Logic::messageDisplayed;
}

