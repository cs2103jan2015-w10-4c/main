#include "Logic.h"
#include "Parser.h"
#include "CommandDisplay.h"

const string CommandDisplay::MESSAGE_COMMAND_TYPE="display";

string CommandDisplay::display() {

	if (Logic::textStorage.empty()){
		return "Empty file";
	}
	else{
		ostringstream overallOss;
		for (unsigned int i = 0; i < Logic::textStorage.size() - 1; i++){
			ostringstream oss;
			oss << i + 1 << ". " << Logic::textStorage[i].ToString() << endl;
			string TextbodyDisplay = oss.str();
			overallOss << TextbodyDisplay;
		}

		int size = Logic::textStorage.size();
		overallOss << size << ". " << Logic::textStorage[size - 1].ToString();
		return overallOss.str();
	}
}