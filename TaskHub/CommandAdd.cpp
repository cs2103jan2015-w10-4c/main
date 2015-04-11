#include <algorithm>
#include "Logic.h"
#include "Parser.h"
#include "CommandAdd.h"
#include "CommandClash.h"
#include "CommandAutoSort.h"

const string CommandAdd::MESSAGE_COMMAND_TYPE = "add";
const string CommandAdd::MESSAGE_ADDED = "Task: \" %s \" added";
const string CommandAdd::MESSAGE_INDICATING_EMPTY = "The input is empty.";
const string CommandAdd::MESSAGE_CLASH = " clashes with existing tasks";
const string CommandAdd::MESSAGE_INVALID_INPUT = "invalid input";

CommandAdd::CommandAdd () {

}

CommandAdd::~CommandAdd () {

}

string CommandAdd::addMessage (string input) {

	Logic::history.setLastCommandType (MESSAGE_COMMAND_TYPE);
	bool isWhiteSpace = all_of(input.begin(), input.end(), isspace);

	// this is to make sure if user just key in empty space or nothing except an "add", nothing will be done
	if (!isWhiteSpace && input != MESSAGE_COMMAND_TYPE ) {
<<<<<<< HEAD
		Task newTask (input);
		bool correct = Task::_isValid;
		if (correct) {
			string message = CommandClash::Clash(input);
			if (message == (input + MESSAGE_CLASH)) {
				sprintf_s(Logic::messageDisplayed,MESSAGE_CLASH.c_str());
				return Logic::messageDisplayed;
			} else {
			Task newTask(input);
			Logic::history.setVectorTextStorage(newTask);
			Logic::history.setLastChangedTask(newTask);
			sprintf_s(Logic::messageDisplayed, MESSAGE_ADDED.c_str(),newTask.ToString().c_str());
			}

=======
		string message = CommandClash::clash(input);
		if (message == (input + MESSAGE_CLASH)) {
			sprintf_s(Logic::messageDisplayed,MESSAGE_CLASH.c_str());
			return Logic::messageDisplayed;
>>>>>>> 1e273b452cce94a1653d972011696149a31727ac
		} else {
			sprintf_s(Logic::messageDisplayed,MESSAGE_INDICATING_EMPTY.c_str());
		}
	} else {
		sprintf_s(Logic::messageDisplayed, MESSAGE_INVALID_INPUT.c_str());
	}
	return Logic::messageDisplayed;

}
string CommandAdd::addOperation(string input) {
	string feedback = CommandAdd::addMessage(input);
	StorageController::updateSaveFile();
	return feedback;
}