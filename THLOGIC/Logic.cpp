
#include <string>
#include <vector>
#include "THLogic.h"

using namespace std;

const int    THLogic::ERROR_INDEX        = -1;
const string THLogic::ADD_LOG            = "adding task.";
const string THLogic::EDIT_LOG           = "editing task.";
const string THLogic::DELETE_LOG         = "deleting task.";
const string THLogic::DELETEALL_LOG      = "deleteingall task.";
const string THLogic::SEARCH_LOG         = "searching task.";
const string THLogic::DONE_LOG           = "marking done.";
const string THLogic::UNDONE_LOG         = "marking undone task.";
const string THLogic::VIEWALL_LOG        = "viewing all task.";
const string THLogic::VIEWTIMED_LOG      = "viewing timed task.";
const string THLogic::VIEWFLOATING_LOG   = "viewing floating task.";
const string THLogic::VIEWDONE_LOG       = "viewing done task.";
const string THLogic::VIEWUNDONE_LOG     = "viewing undone task.";
const string THLogic::VIEWDEADLINE_LOG   = "viewing deadline task.";
const string THLogic::VIEWOVERDUE_LOG    = "viewing overdue task.";
const string THLogic::VIEWTODAY_LOG      = "viewing today task.";
const string THLogic::UNDO_LOG           = "undoing operation.";
const string THLogic::REDO_LOG           = "redoing operation.";
const string THLogic::REFRESH_LOG        = "refreshing tasklist.";
const string THLogic::EXIT_LOG           = "Exiting program.";


// retrieve storage infomation upon construction
THLogic::THLogic() {
	_executor.openFile();
}

// executes the user command
// _display is adjusted after this function is executed
void THLogic::runInput(string inputString, THUtility::PageType pageType) {
	_parser.parseInput(inputString);
	THCommand parsedCommand = _parser.retrieveCommand();
	executeCommand(parsedCommand, pageType);
}

// assist UI to retrieve display information after execution of user command
THDisplay THLogic::getDisplay() {
	return _display;
}

// adjust the user command based on different command types and 
// interact with functionalities of the executor to execute the program.
void THLogic::executeCommand(THCommand parsedCommand, THUtility::PageType pageType) {
	THUtility::CommandType command = parsedCommand.getCommand();
	
	THLogging& Logging = THLogging::getInstance();
	
	switch(command) {
		case THUtility::CommandType::ADD: {
			THTask taskToBeAdded;
			_commandInterpreter.interpretAdd(parsedCommand, taskToBeAdded);
			Logging.addLog(ADD_LOG);
			_display = _executor.addTask(taskToBeAdded);
			break;
		}

		case THUtility::CommandType::DELETE: {
			Logging.addLog(DELETE_LOG);
			if(parsedCommand.hasDetail()) {    //check whether user has input an index
				int deleteIndex;
				_commandInterpreter.interpretDelete(parsedCommand, deleteIndex);
				
				_display = _executor.deleteTask(deleteIndex, pageType);
			} else {
				_display = _executor.deleteTask(ERROR_INDEX, pageType);
			}
			
			break;
		}

		case THUtility::CommandType::DELETEALL: {
			Logging.addLog(DELETEALL_LOG);
			_display = _executor.deleteAll();
			break;
		}								   

		case THUtility::CommandType::EDIT: {
			int editIndex;
			THTask taskToBeEdited;
			
			Logging.addLog(EDIT_LOG);
			
			_commandInterpreter.interpretEdit(parsedCommand, editIndex, taskToBeEdited);
			_display = _executor.editTask(editIndex, taskToBeEdited, pageType);
			
			break;
		}

		case THUtility::CommandType::DONE: {
			Logging.addLog(DONE_LOG);
			
			if(parsedCommand.hasDetail()) {
				int doneIndex;
				_commandInterpreter.interpretDone(parsedCommand, doneIndex);
				_display = _executor.markDone(doneIndex, pageType);
			} else{
				_display = _executor.markDone(ERROR_INDEX, pageType);
			}
			
			break;
			
		}

		case THUtility::CommandType::UNDONE: {
			Logging.addLog(UNDONE_LOG);
			
			if(parsedCommand.hasDetail()) {
				int undoneIndex;
				_commandInterpreter.interpretUndone(parsedCommand, undoneIndex);
				_display = _executor.markUndone(undoneIndex, pageType);
			} else{
				_display = _executor.markUndone(ERROR_INDEX, pageType);
			}
			
			break;
		}

		case THUtility::SEARCH: {
			vector<string> keywordStorage;
			
			Logging.addLog(SEARCH_LOG);
			
			_commandInterpreter.interpretSearch(parsedCommand, keywordStorage);
			_display = _executor.searchTask(keywordStorage);
			break;
		}
		
		case THUtility::CommandType::UNDO:{
			Logging.addLog(UNDO_LOG);
			
			_display = _executor.undo(pageType);
			break;
	    }

		case THUtility::CommandType::REDO:{
			Logging.addLog(REDO_LOG);
			
			_display = _executor.redo(pageType);
			break;
	    }

		
		case THUtility::CommandType::VIEWALL: {
			Logging.addLog(VIEWALL_LOG);
			
			_display = _executor.viewAll();
			break;
		}
		
		case THUtility::CommandType::VIEWDEADLINE: {
			Logging.addLog(VIEWDEADLINE_LOG);
			
			_display = _executor.viewDeadlineTask();
			break;
		}

		case THUtility::CommandType::VIEWTIMED: {
			Logging.addLog(VIEWTIMED_LOG);
			
			_display = _executor.viewTimedTask();
			break;
		}

		case THUtility::CommandType::VIEWFLOATING: {
			Logging.addLog(VIEWFLOATING_LOG);
			
			_display = _executor.viewFloatingTask();
			break;
		}

		case THUtility::CommandType::VIEWTODAY: {
			Logging.addLog(VIEWTODAY_LOG);
			
			_display = _executor.viewToday();
			break;
		}

		case THUtility::CommandType::VIEWDONE: {
			Logging.addLog(VIEWDONE_LOG);
			
			_display = _executor.viewDone();
			break;
		}

		case THUtility::CommandType::VIEWUNDONE: {
			Logging.addLog(VIEWUNDONE_LOG);
			
			_display = _executor.viewUndone();
			break;
		}

		case THUtility::CommandType::VIEWOVERDUE: {
			Logging.addLog(VIEWOVERDUE_LOG);
			
			_display = _executor.viewOverdue();
			break;
		}
		
		case THUtility::CommandType::REFRESH: {
			Logging.addLog(REFRESH_LOG);
			
			_display = _executor.refresh(pageType);
			break;
		}

		case THUtility::CommandType::EXIT: {
			Logging.addLog(EXIT_LOG);
			
			exit(0);
		}

		default: {
			_display = _executor.invalidCommand(pageType);
		}
	}
}
