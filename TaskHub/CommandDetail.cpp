#include "CommandDetail.h"
#include "LogicController.h"
#include "Parser.h"

const string CommandDetail::MESSAGE_COMMAND_TYPE="detail";
const string CommandDetail::MESSAGE_INVALID_INDEX="The index is invalid";
const string CommandDetail::MESSAGE_DETAIL="Task detail is shown";
string CommandDetail::FEEDBACK_SYSTEM;
const char INTEGER_ZERO = '0';
const char INTEGER_NINE = '9';

string CommandDetail::detailMessage(string taskIndex) {
	FEEDBACK_SYSTEM.clear();

	if(checkInputValidation(taskIndex)) {
		unsigned int index;
		istringstream in(taskIndex);
		in >> index;
		
		if (index > StorageDatabase::taskHistory.getVectorTextStorage().size() || index <= 0) {
			FEEDBACK_SYSTEM = MESSAGE_INVALID_INDEX;
			return "";
		}
		else {
			vector<Task> temp=StorageDatabase::taskHistory.getVectorTextStorage();
			FEEDBACK_SYSTEM = MESSAGE_DETAIL;
			return temp[index -1].ToString();
		}
	}
	else {
		FEEDBACK_SYSTEM = MESSAGE_INVALID_INDEX;
		return "";	
	}
}

bool CommandDetail::checkInputValidation(string taskIndex) {
	bool isValid=true;

	for(unsigned int i=0; i<taskIndex.size()&&isValid;i++) {
		if(taskIndex[i]<INTEGER_ZERO || taskIndex[i]>INTEGER_NINE) {
			isValid=false;
		}
	}
	return isValid;
}

