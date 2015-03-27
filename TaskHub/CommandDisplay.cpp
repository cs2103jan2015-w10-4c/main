#include "Logic.h"
#include "Parser.h"
#include "CommandDisplay.h"

const string CommandDisplay::MESSAGE_COMMAND_TYPE="display";
const string CommandDisplay::MESSAGE_EMPTY_FILE="The file is empty";

string CommandDisplay::display() {

	if (Logic::history.getVectorTextStorage().empty()){
		sprintf_s(Logic::messageDisplayed,MESSAGE_EMPTY_FILE.c_str());
		return Logic::messageDisplayed;

	} else {
		ostringstream totalTask;
		for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() - 1; i++){
			ostringstream oss;
			oss << i + 1 << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
			string TaskDisplay = oss.str();
			totalTask << TaskDisplay;
		}

		int size = Logic::history.getVectorTextStorage().size();
		totalTask << size << ". " << Logic::history.getVectorTextStorage()[size - 1].ToString();
		return totalTask.str();
	}
}