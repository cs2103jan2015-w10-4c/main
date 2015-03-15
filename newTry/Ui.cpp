
#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";
const string UI::MESSAGE_TERMINATION = "Programme terminated.";

const string UI::MESSAGE_ERROR = "Invalid command.";


string UI::displayWelcomeMessage() {
	storage::programmeInitialising();
	Logic::getStorage();

	return MESSAGE_WELCOME;
}

void UI::showToUser(string text) {
	cout << text << endl;
}

string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);

	return userCommand;
}

string UI::executeUserCommand(string userCommand) {
	string commandTypeString;
	string TextbodyString;

	commandTypeString = getFirstWord(userCommand);
	TextbodyString = removeFirstWord(userCommand);

	transform(commandTypeString.begin(), commandTypeString.end(), commandTypeString.begin(), ::tolower);
	
	COMMAND_TYPE commandType;
	commandType = determineCommandType(commandTypeString, TextbodyString);

	switch (commandType) {
	case HELP:
		return help();
	case ADD_Textbody:
		return Logic::addTextbody(TextbodyString);
	case SEARCH:
		return Logic::search(TextbodyString);
	case UPDATE:
		return Logic::updateTextbody(TextbodyString);
	case DELETE_Textbody:
		return Logic::deleteTextbody(TextbodyString);
	case DISPLAY_TextbodyS:
		return Logic::display();
	case MARK_DONE:
		return Logic::MarkDone(TextbodyString);
	case UNDO:
		return Logic::undo();
	case REDO:
		return Logic::redo();
	case EXIT:
		storage::programmeTerminating();
		cout << MESSAGE_TERMINATION << endl;;
		exit(0);
	case INVALID:
	default:
		return MESSAGE_ERROR;
	}
}

UI::COMMAND_TYPE UI::determineCommandType(string commandTypeString, string TextbodyString) {
	if (commandTypeString == "help") {
		return COMMAND_TYPE::HELP;
	}
	else if (commandTypeString == "add") {
		return COMMAND_TYPE::ADD_Textbody;
	}
	else if (commandTypeString == "update") {
		return COMMAND_TYPE::UPDATE;
	}
	else if (commandTypeString == "delete") {
		return COMMAND_TYPE::DELETE_Textbody;
	}
	else if (commandTypeString == "search") {
		return COMMAND_TYPE::SEARCH;
	}
	else if (commandTypeString == "display") {
		return COMMAND_TYPE::DISPLAY_TextbodyS;
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
	else if (commandTypeString == "exit") {
		return COMMAND_TYPE::EXIT;
	}
	else{
		return COMMAND_TYPE::INVALID;
	}
}

string UI::getFirstWord(string userCommand) {
	return userCommand.substr(0, userCommand.find(' '));
}

string UI::removeFirstWord(string userCommand) {
	return userCommand.substr(userCommand.find_first_of(" ") + 1);
}

string UI::help() {
	cout << "Some examples:\n";

	cout << "Add: add meeting -from 1200 -to 1400 25/12\n";
	cout << "Display all: display \n";
	cout << "Display Static Textbodys: display static\n";
	cout << "Display Deadline Textbodys: display deadline\n";
	cout << "Display Unfinished Textbodys: display unfinished\n";
	cout << "Display Finished Textbodys: display finished\n";
	cout << "Display Floating Textbodys: display floating\n";
	
	cout << "Update: Update 1 -from 1400 -to 1500 23/12\n";
	cout << "Search: search meeting\n";
	cout << "Delete: delete 1\n";
	
	cout << "Undo: undo\n";
	cout << "Redo: redo\n";
	cout << "Exit: exit\n";

	return "";
}
