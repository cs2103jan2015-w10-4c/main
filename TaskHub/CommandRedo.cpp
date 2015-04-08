#include "Logic.h"
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

	vector<Task> temporary=Logic::history.getVectorTextStorage();

	if (Logic::history.getLastCommandType() == COMMAND_TYPE_ADD){
		
		temporary.push_back(Logic::history.getLastChangedTask());
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_ADD.c_str());
		return Logic::messageDisplayed;
	}
	else if (Logic::history.getLastCommandType()  == COMMAND_TYPE_UPDATE){
		temporary[Logic::history.getLastChangedTaskIndex()] = Logic::history.getLastChangedTask();
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_UPDATE.c_str());
		return Logic::messageDisplayed;
	}
	else if (Logic::history.getLastCommandType()  == COMMAND_TYPE_DELETE){
		temporary.erase(temporary.begin() + Logic::history.getLastChangedTaskIndex());
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_DELETE.c_str());
		return Logic::messageDisplayed;
	}
	else if (Logic::history.getLastCommandType()  == COMMAND_TYPE_CLEAR){
		temporary=Logic::history.getBackUpStorage();
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_CLEAR.c_str());
		return Logic::messageDisplayed;
	}
	else if (Logic::history.getLastCommandType()  == COMMAND_TYPE_UNCOMPLETE){
		temporary[Logic::history.getLastChangedTaskIndex()].markUncompleted();
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_UNCOMPLETE.c_str());
		return Logic::messageDisplayed;
	}
	else if (Logic::history.getLastCommandType()  == COMMAND_TYPE_DONE){
		temporary[Logic::history.getLastChangedTaskIndex()].MarkDone();
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_COMMAND_REDO.c_str(), COMMAND_TYPE_DONE.c_str());
		return Logic::messageDisplayed;
	}
	else{
		return MESSAGE_ERROR;
	}

}
