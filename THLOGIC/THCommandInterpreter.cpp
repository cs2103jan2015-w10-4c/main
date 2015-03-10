#include "THCommandInterpreter.h"
#include <cctype>
#include "assert.h"


using namespace std;

const int    THCommandInterpreter::INVALID_INDEX        = -1;
const string THCommandInterpreter::EMPTY_CONTENT        = "";
const string THCommandInterpreter::SPACE                = " "; 
const string THCommandInterpreter::NO_INDEX_EXCEPTION   = "No Index found£¡";
const string THCommandInterpreter::INTERPRET_ADD_LOG    = "Interpreting add command.";
const string THCommandInterpreter::INTERPRET_EDIT_LOG   = "Interpreting edit command.";
const string THCommandInterpreter::INTERPRET_DELETE_LOG = "Interpreting delete command.";
const string THCommandInterpreter::INTERPRET_DONE_LOG   = "Interpreting done command.";
const string THCommandInterpreter::INTERPRET_UNDONE_LOG = "Interpreting undone command.";
const string THCommandInterpreter::INTERPRET_SEARCH_LOG = "Interpreting search command.";

THCommandInterpreter::THCommandInterpreter(){
}

// This function extract the task to be added from the THCommand object
// and store into a THTask object.
// precondition : 1. The THCommand object must have a commandType of ADD.
//                2. The THTask object should be a empty task.  
// postcondition: task details of the new task is stored into taskToBeAdded
void THCommandInterpreter::interpretAdd(THCommand addCommand, THTask& taskToBeAdded) {
	// the commandtype must be ADD in order for the method to function correctly
	//assert (addCommand.getCommand() == THUtilities::CommandType::ADD);
	
	THLogging& logAdd = THLogging::getInstance();
	logAdd.addLog(INTERPRET_ADD_LOG);
	logAdd.saveLog();

	if(addCommand.haveDetail()) {
		taskToBeAdded.setTaskName(addCommand.getDescription());
	} else {
		taskToBeAdded.setTaskName(EMPTY_CONTENT);
	}

	if(addCommand.haveStartingDate()) {
		taskToBeAdded.setStartingDate(addCommand.getStartingDate());
	} else {
		taskToBeAdded.setStartingDate(EMPTY_CONTENT);
	}

	if(addCommand.haveStartingTime()) {
		taskToBeAdded.setStartingTime(addCommand.getStartingTime());
	} else {
		taskToBeAdded.setStartingTime(EMPTY_CONTENT);
	}

	if(addCommand.haveEndingDate()) {
		taskToBeAdded.setEndingDate(addCommand.getEndingDate());
	} else {
		taskToBeAdded.setEndingDate(EMPTY_CONTENT);
	}

	if(addCommand.haveEndingTime()) {
		taskToBeAdded.setEndingTime(addCommand.getEndingTime());
	} else {
		taskToBeAdded.setEndingTime(EMPTY_CONTENT);
	}
}

// This function helped to identify the index of the target task to be edited
// and store the edit details into a THTask object.
// precondition : 1.The THCommand object must have a commandType of EDIT.
//                2.The editIndex should not be initialised before 
//                  passing to the function.
//                3.The THTask object should be a empty task.
// postcondition: 1.The desired modification to different attributes of the 
//                  target task are stored separatedy in the taskToBeEdited.
//                2.editIndex is adjusted to the index of the target task to be edited.
void THCommandInterpreter::interpretEdit(THCommand editCommand, int& editIndex, THTask& taskToBeEdited) {
	//assert (editCommand.getCommand() == THUtilities::CommandType::EDIT);
	
	THLogging& logEdit = THLogging::getInstance();
	logEdit.addLog(INTERPRET_EDIT_LOG);
	logEdit.saveLog();

	string editDetail = editCommand.getDescription();
	string editedTaskName;
	
	try {
		// extract the index of the target task and the new task name
	    // proposed by the user from the editDetail string.
		separateIndexDetail(editDetail, editIndex, editedTaskName); 
	} catch (string&){
		// the exception thrown indicates that the function is unable to
		// obtain a valid index in the editDetail
		editIndex = INVALID_INDEX; 
	}
	if(!editedTaskName.empty()){
		taskToBeEdited.setTaskName(editedTaskName);
	} else {
		taskToBeEdited.setTaskName(EMPTY_CONTENT);
	}

	if(editCommand.haveStartingDate()) {
		taskToBeEdited.setStartingDate(editCommand.getStartingDate());
	} else {
		taskToBeEdited.setStartingDate(EMPTY_CONTENT);
	}

	if(editCommand.haveStartingTime()) {
		taskToBeEdited.setStartingTime(editCommand.getStartingTime());
	} else {
		taskToBeEdited.setStartingTime(EMPTY_CONTENT);
	}

	if(editCommand.haveEndingDate()) {
		taskToBeEdited.setEndingDate(editCommand.getEndingDate());
	} else {
		taskToBeEdited.setEndingDate(EMPTY_CONTENT);
	}

	if(editCommand.haveEndingTime()) {
		taskToBeEdited.setEndingTime(editCommand.getEndingTime());
	} else {
		taskToBeEdited.setEndingTime(EMPTY_CONTENT);
	}
}

// This function helps to interpret the seachCommand by extracting the 
// relevant search keywords and store them in a vector of string.
// precondition : The THCommand object must have a commandType of SEARCH.
// postcondition: The different search keywords that required by the user are extracted and
//                stored into keywordStorage separately. The vector stores a maximum of 
//                5 strings. 
void THCommandInterpreter::interpretSearch(THCommand searchCommand, vector<string>& keywordStorage) {
	//assert (searchCommand.getCommand() == THUtilities::CommandType::SEARCH);
	
	THLogging& logSearch = THLogging::getInstance();
	logSearch.addLog(INTERPRET_SEARCH_LOG);
	logSearch.saveLog();
	
	keywordStorage.clear();

	if(searchCommand.haveDetail()) {
		keywordStorage.push_back(searchCommand.getDescription());
	} else {
		keywordStorage.push_back(EMPTY_CONTENT);
	}
	
	if(searchCommand.haveStartingDate()) {
		keywordStorage.push_back(searchCommand.getStartingDate());
	} else {
		keywordStorage.push_back(EMPTY_CONTENT);
	}

	if (searchCommand.haveStartingTime()) {
		keywordStorage.push_back(searchCommand.getStartingTime());
	} else {
		keywordStorage.push_back(EMPTY_CONTENT);
	}

	if (searchCommand.haveEndingDate()) {
		keywordStorage.push_back(searchCommand.getEndingDate());
	} else {
		keywordStorage.push_back(EMPTY_CONTENT);
	}

	if (searchCommand.haveEndingTime()) {
		keywordStorage.push_back(searchCommand.getEndingTime());
	} else {
		keywordStorage.push_back(EMPTY_CONTENT);
	}

}

// precondition : The THCommand object must have a commandType of DELETE.
// postcondition: 1. deleteIndex is adjusted to the index of the task to be deleted
//                   if the index exists, otherwise, an exception is thrown
void THCommandInterpreter::interpretDelete(THCommand deleteCommand, int& deleteIndex) {
	//assert (deleteCommand.getCommand() == THUtilities::CommandType::DELETE);
	
	THLogging& logDelete = THLogging::getInstance();
	logDelete.addLog(INTERPRET_DELETE_LOG);
	logDelete.saveLog();

	string deleteIndexString = deleteCommand.getDescription();
	try {
		deleteIndex              = convertStringToInt(deleteIndexString);
	} catch (string& ) {
		deleteIndex = INVALID_INDEX;
	}
}

// precondition : The THCommand object must have a commandType of DONE.
// postcondition: doneIndex is adjusted to the index of the task to be marked done
//                if the index exists, otherwise, an exception is thrown
void THCommandInterpreter::interpretDone(THCommand doneCommand, int& doneIndex) {
	//assert (doneCommand.getCommand() == THUtilities::CommandType::DONE);

	THLogging& logDone = THLogging::getInstance();
	logDone.addLog(INTERPRET_DONE_LOG);
	logDone.saveLog();

	string doneIndexString = doneCommand.getDescription();

	try {
		doneIndex              = convertStringToInt(doneIndexString);
	} catch (string&) {
		doneIndex = INVALID_INDEX;
	} 
}

// precondition : The THCommand object must have a commandType of UNDONE.
// postcondition: undoneIndex is adjusted to the index of the task to be marked undone.
//                if the index exists, otherwise, an exception is thrown
void THCommandInterpreter::interpretUndone(THCommand undoneCommand, int& undoneIndex) {
	//assert (undoneCommand.getCommand() == THUtilities::CommandType::UNDONE);

	THLogging& logUndone = THLogging::getInstance();
	logUndone.addLog(INTERPRET_UNDONE_LOG);
	logUndone.saveLog();

	string undoneIndexString = undoneCommand.getDescription();

	try {
		undoneIndex              = convertStringToInt(undoneIndexString);
	} catch (string&){
		// exception will be thrown if there is no information for index
		undoneIndex = INVALID_INDEX;
	}

}


// This function serves to separate the index of the task to be edited and the proposed 
// new task name by the user from a string editDetail.
// precondition : The index is located at the beginning of editDetail and separated
//                with the rest by a space.
// postcondition: 1. Index of the target task is stored in editIndex.
//                2. An exception is thrown if no valid index found.
//                2. The new task name is stored into editedTaskName.
void THCommandInterpreter::separateIndexDetail(string editDetail, int& editIndex, string& editedTaskName) {
	int taskNameLocation;
	int indexLocation = editDetail.find_first_of(SPACE);

	if(indexLocation != string::npos) {
		string indexString = editDetail.substr(0, indexLocation);
		editIndex          = convertStringToInt(indexString);
		taskNameLocation = editDetail.find_first_not_of(SPACE, ++indexLocation);
		editedTaskName     = editDetail.substr(taskNameLocation);
	} else if(!editDetail.empty()) {
		editIndex = convertStringToInt(editDetail);
		editedTaskName = EMPTY_CONTENT;
	} else {
		throw NO_INDEX_EXCEPTION;
	}
	
	
}

int THCommandInterpreter::convertStringToInt(string convertString) {
	if(convertString.empty()){
		throw NO_INDEX_EXCEPTION;
	} else {
		return atoi(convertString.c_str());
	}
}