//@author A0115365J
#include "LogicController.h"
#include "CommandRedo.h"


const string redoChange::MESSAGE_COMMAND_REDO = "%s command is redone";
const string redoChange::MESSAGE_ERROR = "previous action cannot be redo";
const string redoChange::COMMAND_TYPE_ADD = "add";
const string redoChange::COMMAND_TYPE_UPDATE = "update";
const string redoChange::COMMAND_TYPE_CLEAR = "clear";
const string redoChange::COMMAND_TYPE_DONE = "done";
const string redoChange::COMMAND_TYPE_UNCOMPLETE = "uncomplete";
const string redoChange::COMMAND_TYPE_DELETE = "delete";

redoChange::redoChange () {

}
redoChange::~redoChange () {

}

string redoChange::redo() {
	//@author A0115365J-reused
	vector<Task> temporary=StorageDatabase::taskHistory.getVectorTextStorage();

	if (StorageDatabase::taskHistory.getLastCommandType() == COMMAND_TYPE_ADD){
		
		temporary.push_back(StorageDatabase::taskHistory.getLastChangedTask());
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_ADD.c_str());
		return Logic::messageDisplayed;
	}
	else if (StorageDatabase::taskHistory.getLastCommandType()  == COMMAND_TYPE_UPDATE){
		temporary[StorageDatabase::taskHistory.getLastChangedTaskIndex()] = StorageDatabase::taskHistory.getLastChangedTask();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_UPDATE.c_str());
		return Logic::messageDisplayed;
	}
	else if (StorageDatabase::taskHistory.getLastCommandType()  == COMMAND_TYPE_DELETE){
		temporary.erase(temporary.begin() + StorageDatabase::taskHistory.getLastChangedTaskIndex());
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_DELETE.c_str());
		return Logic::messageDisplayed;
	}
	else if (StorageDatabase::taskHistory.getLastCommandType()  == COMMAND_TYPE_CLEAR){
		temporary=StorageDatabase::taskHistory.getBackUpStorage();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_CLEAR.c_str());
		return Logic::messageDisplayed;
	}
	else if (StorageDatabase::taskHistory.getLastCommandType()  == COMMAND_TYPE_UNCOMPLETE){
		temporary[StorageDatabase::taskHistory.getLastChangedTaskIndex()].markUncompleted();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_UNCOMPLETE.c_str());
		return Logic::messageDisplayed;
	}
	else if (StorageDatabase::taskHistory.getLastCommandType()  == COMMAND_TYPE_DONE){
		temporary[StorageDatabase::taskHistory.getLastChangedTaskIndex()].MarkDone();
		StorageDatabase::taskHistory.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_DONE.c_str());
		return Logic::messageDisplayed;
	}
	else{
		return MESSAGE_ERROR;
	}

}
