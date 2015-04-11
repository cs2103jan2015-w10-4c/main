#include "CommandDetail.h"
#include "Logic.h"
#include "Parser.h"

const string CommandDetail::MESSAGE_COMMAND_TYPE="detail";
const string CommandDetail::MESSAGE_INVALID_INDEX="The index is invalid";
const string CommandDetail::MESSAGE_DETAIL="Details of Task: %s is shown";
string CommandDetail::SYSTEM_FEEDBACK;

string CommandDetail::detailMessage(string taskIndex) {
	SYSTEM_FEEDBACK.clear();
	if(checkInputValidation(taskIndex)){

		unsigned int index;
		istringstream in(taskIndex);
		in >> index;
		
		if (index > Logic::history.getVectorTextStorage().size() || index <= 0){
			SYSTEM_FEEDBACK = MESSAGE_INVALID_INDEX;
			return "";
		}
		else{
			vector<Task> temp=Logic::history.getVectorTextStorage();
			
			SYSTEM_FEEDBACK = MESSAGE_DETAIL;
			return temp[index -1].ToString();
		}
	}
	else{
		
		SYSTEM_FEEDBACK = MESSAGE_INVALID_INDEX;
		return "";
		
	}

}

bool CommandDetail::checkInputValidation(string taskIndex){
	
	bool isValid=true;
	for(unsigned int i=0; i<taskIndex.size()&&isValid;i++){
		if(taskIndex[i]<'0' || taskIndex[i]>'9')
			isValid=false;
	}

	return isValid;
}

