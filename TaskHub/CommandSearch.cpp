//@author A0115365J
#include <algorithm>
#include "LogicController.h"
#include "Parser.h"
#include "CommandSearch.h"


const string CommandSearch::MESSAGE_COMMAND_TYPE = "search";
const string CommandSearch::MESSAGE_CANNOT_FIND = "Cannot find message";
const string CommandSearch::MESSAGE_EMPTY_FILE = "The file is empty";
const string CommandSearch::MESSAGE_IS_SHOWN = "Message is shown";
vector <string> CommandSearch::messageDisplayed;

CommandSearch::CommandSearch () {

}

CommandSearch::~CommandSearch () {

}

string CommandSearch::searchMessage (string input) {
	
	if (StorageDatabase::taskHistory.getVectorTextStorage().empty()){
		sprintf_s(Logic::messageDisplayed,MESSAGE_EMPTY_FILE.c_str());
		return Logic::messageDisplayed;
	}
	else{
		vector<string> output;
		vector<Task> temp = StorageDatabase::taskHistory.getVectorTextStorage();
		vector<string> description;

		transform(input.begin(),input.end(),input.begin(),:: tolower);

		for (unsigned int i = 0; i < temp.size(); i++){//@author A0115365J-reused
			string _Taskname = (temp[i]).getTaskName();
			transform(_Taskname.begin(),_Taskname.end(),_Taskname.begin(),:: tolower);
			description.push_back(_Taskname);
		}

		for (unsigned int j = 0; j < description.size(); j++){
			size_t found= description[j].find(input);	
			if (found != string::npos){//@author A0115365J-reused
					ostringstream oss;
					oss << j + 1 << "." << temp[j].ToString() << endl;
					string TaskDisplay = oss.str();
					output.push_back(TaskDisplay);
				}
			}
		//@author A0115365J-reused
		if (output.empty()) {
			sprintf_s(Logic::messageDisplayed, MESSAGE_CANNOT_FIND.c_str());
			return Logic::messageDisplayed;
		} else {
			CommandSearch::messageDisplayed.clear();
			CommandSearch::messageDisplayed = output;
			sprintf_s(Logic::messageDisplayed, MESSAGE_IS_SHOWN.c_str());
			return Logic::messageDisplayed;
		}	

	}
}
