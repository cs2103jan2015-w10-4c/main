//@author A0115365J
#include "CommandInterpreter.h"

const string CommandInterpreter::MESSAGE_TERMINATION = "Programme terminated.";
const string CommandInterpreter::MESSAGE_ERROR = "Invalid command.";
const string CommandInterpreter::COMMAND_ADD = "add";
const string CommandInterpreter::COMMAND_DELETE = "delete";
const string CommandInterpreter::COMMAND_CLEAR = "clear";
const string CommandInterpreter::COMMAND_UPDATE = "update";
const string CommandInterpreter::COMMAND_REDO = "redo";
const string CommandInterpreter::COMMAND_UNDO = "undo";
const string CommandInterpreter::COMMAND_SORT = "sort";
const string CommandInterpreter::COMMAND_CLASH = "clash";
const string CommandInterpreter::COMMAND_DONE = "done";
const string CommandInterpreter::COMMAND_SHOW = "show";
const string CommandInterpreter::COMMAND_SEARCH = "search";
const string CommandInterpreter::COMMAND_UNCOMPLETE = "uncompleted";
const string CommandInterpreter::COMMAND_DISPLAY = "display";
const string CommandInterpreter::COMMAND_RECURRING = "recurring";
const string CommandInterpreter::COMMAND_HELP = "help";
const string CommandInterpreter::COMMAND_EXIT = "exit";
const string CommandInterpreter::COMMAND_DETAIL = "detail";

CommandInterpreter::CommandInterpreter () {

}

CommandInterpreter::~CommandInterpreter () {

}

string CommandInterpreter::executeUserCommand(string userCommand) {
	string commandTypeString;
	string TaskString;

	commandTypeString = getFirstWord(userCommand);
	TaskString = removeFirstWord(userCommand);

	transform(commandTypeString.begin(), commandTypeString.end(), commandTypeString.begin(), ::tolower);
	
	COMMAND_TYPE commandType;
	commandType = determineCommandType(commandTypeString, TaskString);

	switch (commandType) {
	case SHOW:
		return Logic::show(TaskString);
	case RECURRING:
		return Logic::recurTask(TaskString);
	case HELP:
		return Logic::help();
	case CLEAR:
		return Logic::clearAll(TaskString);
	case ADD_TASK:
		return Logic::addTask(TaskString);
	case UPDATE:
		return Logic::updateTask(TaskString);
	case SORT:
		return Logic::sort();
	case DELETE_TASK:
		return Logic::deleteTask(TaskString);
	case DISPLAY_TASK:
		return Logic::display(TaskString);
	case MARK_DONE:
		return Logic::MarkDone(TaskString);
	case UNCONPLETE:
		return Logic::markUncompleted(TaskString);
	case SEARCH:
		return Logic::search(TaskString);
	case DETAIL:
		return Logic::getDetail(TaskString);
	case CHECK:
		return Logic::checkClash(TaskString);
	case UNDO:
		return Logic::undo();
	case REDO:
		return Logic::redo();
	case EXIT:
		StorageController::updateSaveFile();
		cout << MESSAGE_TERMINATION << endl;;
		exit(0);
	case INVALID:
	default:
		return MESSAGE_ERROR;
	}
}

CommandInterpreter::COMMAND_TYPE CommandInterpreter::determineCommandType(string commandTypeString, string TaskString) {
	if (commandTypeString == COMMAND_HELP) {
		return COMMAND_TYPE::HELP;
	}
	else if (commandTypeString == COMMAND_ADD) {
		return COMMAND_TYPE::ADD_TASK;
	} 
	else if (commandTypeString == COMMAND_CLEAR) {
		return COMMAND_TYPE::CLEAR;
	}
	else if (commandTypeString == COMMAND_UPDATE) {
		return COMMAND_TYPE::UPDATE;
	}
	else if (commandTypeString == COMMAND_RECURRING) {
		return COMMAND_TYPE::RECURRING;
	}
	else if (commandTypeString == COMMAND_DELETE) {
		return COMMAND_TYPE::DELETE_TASK;
	}
	else if (commandTypeString == COMMAND_SEARCH) {
		return COMMAND_TYPE::SEARCH;
	}
	else if (commandTypeString == COMMAND_DISPLAY) {
		return COMMAND_TYPE::DISPLAY_TASK;
	}
	else if (commandTypeString == COMMAND_SHOW) {
		return COMMAND_TYPE::SHOW;
	} 
	else if (commandTypeString == COMMAND_DETAIL) {
		return COMMAND_TYPE::DETAIL;
	}
	else if (commandTypeString == COMMAND_SORT) {
		return COMMAND_TYPE::SORT;
	}
	else if (commandTypeString == COMMAND_DONE) {
		return COMMAND_TYPE::MARK_DONE;
	}
	else if (commandTypeString == COMMAND_UNDO) {
		return COMMAND_TYPE::UNDO;
	} 
	else if (commandTypeString == COMMAND_CLASH) {
		return COMMAND_TYPE::CHECK;
	}
	else if (commandTypeString == COMMAND_REDO) {
		return COMMAND_TYPE::REDO;
	}
	else if (commandTypeString == COMMAND_UNCOMPLETE) {
		return COMMAND_TYPE::UNCONPLETE;
	}
	else if (commandTypeString == COMMAND_EXIT) {
		return COMMAND_TYPE::EXIT;
	}
	else{
		return COMMAND_TYPE::INVALID;
	}
}

string CommandInterpreter::getFirstWord(string userCommand) {
	return userCommand.substr(0, userCommand.find(' '));
}

string CommandInterpreter::removeFirstWord(string userCommand) {
	return userCommand.substr(userCommand.find_first_of(" ") + 1);
}
