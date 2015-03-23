#include "Logic.h"
#include "Parser.h"
#include "CommandDisplay.h"

const string CommandDisplay::MESSAGE_COMMAND_TYPE="display";

string CommandDisplay::display() {

	if (Logic::history.getVectorTextStorage().empty()){
		return "Empty file";
	}
	else{
		ostringstream overallOss;
		for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() - 1; i++){
			ostringstream oss;
			oss << i + 1 << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
			string TaskDisplay = oss.str();
			overallOss << TaskDisplay;
		}

		int size = Logic::history.getVectorTextStorage().size();
		overallOss << size << ". " << Logic::history.getVectorTextStorage()[size - 1].ToString();
		return overallOss.str();
	}
}