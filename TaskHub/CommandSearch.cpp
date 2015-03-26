#include "Logic.h"
#include "Parser.h"
#include "CommandSearch.h"
#include <algorithm>

const string CommandSearch::MESSAGE_COMMAND_TYPE="search";
const string CommandSearch::MESSAGE_CANNOT_FIND="Cannot find message";
const string CommandSearch::MESSAGE_EMPTY_FILE="The file is empty";

string CommandSearch::searchMessage (string input) {

	if (Logic::history.getVectorTextStorage().empty()){
		return MESSAGE_EMPTY_FILE;
	}
	else{
		vector<string> output;
		vector<Task> temp=Logic::history.getVectorTextStorage();
		vector<string> description;

		for (unsigned int i = 0; i < temp.size(); i++){
			string _Taskname = (temp[i]).getTaskName();
			description.push_back(_Taskname);}

		for (unsigned int j = 0; j < description.size(); j++){
			size_t found= description[j].find(input);	
			if (found!=string::npos){
					ostringstream oss;
					oss << j + 1 << "." << temp[j].ToString() << endl;
					string TaskDisplay = oss.str();
					output.push_back(TaskDisplay);
				}
			}

		return CommandSearch::printVector(output);
	}

}


string CommandSearch::printVector(vector<string> output){
	ostringstream oss;
	for (unsigned int i = 0; i < output.size(); i++){
		oss << output[i];
	}
	return oss.str();
}
