#include "CommandInterpreter.h"

const string CommandInterpreter::MESSAGE_TERMINATION = "Programme terminated.";

const string CommandInterpreter::MESSAGE_ERROR = "Invalid command.";

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
	case HELP:
		return Logic::help();
	case ADD_Task:
		return Logic::addTask(TaskString);
	case UPDATE:
		return Logic::updateTask(TaskString);
	case DELETE_Task:
		return Logic::deleteTask(TaskString);
	case DISPLAY_TaskS:
		return Logic::display(TaskString);
	case MARK_DONE:
		return Logic::MarkDone(TaskString);
	case UNCONPLETE:
		return Logic::markUncompleted(TaskString);
	case SEARCH:
		return Logic::search(TaskString);
	case UNDO:
		return Logic::undo();
	case REDO:
		return Logic::redo();
	case EXIT:
		StorageController::programmeTerminating();
		cout << MESSAGE_TERMINATION << endl;;
		exit(0);
	case INVALID:
	default:
		return MESSAGE_ERROR;
	}
}

CommandInterpreter::COMMAND_TYPE CommandInterpreter::determineCommandType(string commandTypeString, string TaskString) {
	if (commandTypeString == "help") {
		return COMMAND_TYPE::HELP;
	}
	else if (commandTypeString == "add") {
		return COMMAND_TYPE::ADD_Task;
	}
	else if (commandTypeString == "update") {
		return COMMAND_TYPE::UPDATE;
	}
	else if (commandTypeString == "delete") {
		return COMMAND_TYPE::DELETE_Task;
	}
	else if (commandTypeString == "search") {
		return COMMAND_TYPE::SEARCH;
	}
	else if (commandTypeString == "display") {
		return COMMAND_TYPE::DISPLAY_TaskS;
	}
	else if (commandTypeString == "show") {
		return COMMAND_TYPE::SHOW;
	}
	else if (commandTypeString == "done") {
		return COMMAND_TYPE::MARK_DONE;
	}
	else if (commandTypeString == "undo") {
		return COMMAND_TYPE::UNDO;
	}
	else if (commandTypeString == "redo") {
		return COMMAND_TYPE::REDO;
	}
	else if (commandTypeString == "uncomplete") {
		return COMMAND_TYPE::UNCONPLETE;
	}
	else if (commandTypeString == "exit") {
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
