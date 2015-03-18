#include "Logic.h"
#include "Parser.h"
#include "DisplayMessage.h"

const string displayingMessage::MESSAGE_COMMAND_TYPE="display";

string displayingMessage::displayMessage() {

	if (Logic::list.empty()){
		return "Empty list";
	}
	else{
		ostringstream overallOss;
		for (unsigned int i = 0; i < Logic::list.size() - 1; i++){
			ostringstream oss;
			oss << i + 1 << ". " << Logic::list[i].ToString() << endl;
			string TextbodyDisplay = oss.str();
			overallOss << TextbodyDisplay;
		}

		int size = Logic::list.size();
		overallOss << size << ". " << Logic::list[size - 1].ToString();
		return overallOss.str();
	}
}