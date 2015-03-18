#include "Logic.h"
#include "Parser.h"
#include "CommandSearch.h"

const string CommandSearch::MESSAGE_COMMAND_TYPE="search";

string CommandSearch::searchMessage (string input) {

	if (Logic::textStorage.empty()){
		return "Empty file";
	}
	else{
		vector<string> output;
		for (unsigned int i = 0; i < Logic::textStorage.size(); i++){
			string _Taskname = (Logic::textStorage[i]).get_TaskName();
			vector<string> description = Logic::splitText(_Taskname);

			for (unsigned int j = 0; j < description.size(); j++){
				if (input == description[j]){
					ostringstream oss;
					oss << i + 1 << "." << Logic::textStorage[i].ToString() << endl;
					string TaskDisplay = oss.str();
					output.push_back(TaskDisplay);
				}
			}
		}

		return Logic::printVector(output);
	}

}