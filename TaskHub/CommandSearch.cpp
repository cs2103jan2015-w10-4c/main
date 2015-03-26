#include "Logic.h"
#include "Parser.h"
#include "CommandSearch.h"

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

		for (unsigned int i = 0; i < temp.size(); i++){
			string _Taskname = (temp[i]).getTaskName();
			vector<string> description = CommandSearch::splitText(_Taskname);

			for (unsigned int j = 0; j < description.size(); j++){
				if (input == description[j]){
					ostringstream oss;
					oss << i + 1 << "." << temp[i].ToString() << endl;
					string TaskDisplay = oss.str();
					output.push_back(TaskDisplay);
				}
			}
		}

		return CommandSearch::printVector(output);
	}

}

vector<string> CommandSearch::splitText(string text){
	vector<string> words;
	string word;
	istringstream in(text);
	copy(istream_iterator<string>(in),
		istream_iterator<string>(),
		back_inserter<vector<string>>(words));

	return words;
}

string CommandSearch::printVector(vector<string> output){
	ostringstream oss;
	for (unsigned int i = 0; i < output.size(); i++){
		oss << output[i];
	}
	return oss.str();
}
