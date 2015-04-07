#include <algorithm>
#include "Logic.h"
#include "Parser.h"
#include "CommandSearch.h"


const string CommandSearch::MESSAGE_COMMAND_TYPE = "search";
const string CommandSearch::MESSAGE_CANNOT_FIND = "Cannot find message";
const string CommandSearch::MESSAGE_EMPTY_FILE = "The file is empty";
const string CommandSearch::MESSAGE_IS_SHOWN = "Message is shown";
vector <string> CommandSearch::messageDisplayed;

string CommandSearch::searchMessage (string input) {

	if (Logic::history.getVectorTextStorage().empty()){
		sprintf_s(Logic::messageDisplayed,MESSAGE_EMPTY_FILE.c_str());
		return Logic::messageDisplayed;
	}
	else{
		vector<string> output;
		vector<Task> temp = Logic::history.getVectorTextStorage();
		vector<string> description;

		transform(input.begin(),input.end(),input.begin(),:: tolower);

		for (unsigned int i = 0; i < temp.size(); i++){
			string _Taskname = (temp[i]).getTaskName();
			transform(_Taskname.begin(),_Taskname.end(),_Taskname.begin(),:: tolower);
			description.push_back(_Taskname);
		}

		for (unsigned int j = 0; j < description.size(); j++){
			size_t found= description[j].find(input);	
			if (found != string::npos){
					ostringstream oss;
					oss << j + 1 << "." << temp[j].ToString() << endl;
					string TaskDisplay = oss.str();
					output.push_back(TaskDisplay);
				}
			}
		
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
/*
string CommandSearch::printVector(vector<string> output){
	ostringstream oss;
	for (unsigned int i = 0; i < output.size(); i++){
		oss << output[i];
	}
	return oss.str();
}
*/