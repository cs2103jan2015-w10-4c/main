#include "Logic.h"
#include "Parser.h"
#include "Search.h"

const string searchingMessage::MESSAGE_COMMAND_TYPE="search";

string searchingMessage::searchMessage (string input) {

	if (Logic::list.empty()){
		return "Empty list";
	}
	else{
		vector<string> output;
		for (unsigned int i = 0; i < Logic::list.size(); i++){
			string _Textbodyname = (Logic::list[i]).get_TextbodyName();
			vector<string> description = Logic::splitText(_Textbodyname);

			for (unsigned int j = 0; j < description.size(); j++){
				if (input == description[j]){
					ostringstream oss;
					oss << i + 1 << "." << Logic::list[i].ToString() << endl;
					string TextbodyDisplay = oss.str();
					output.push_back(TextbodyDisplay);
				}
			}
		}

		return Logic::printVector(output);
	}

}