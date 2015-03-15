#include <sstream>
#include "Logic.h"

vector<Textbody> Logic::list;
string Logic::lastCommandType;
int Logic::lastChangedTextbodyIndex;
Textbody Logic::lastChangedTextbody;
Textbody Logic::lastUnchangedTextbody;

void Logic::getStorage(){
	vector<string> Logic = storage::returnTextbody();

	for (unsigned int i = 0; i < Logic.size(); i++){
		string textbody = removeFirstWord(Logic[i]);
		Textbody newTextbody(textbody, "copy");
		list.push_back(newTextbody);
	}
}

string Logic::addTextbody(string input){
	lastCommandType = "add";

	Textbody newTextbody(input);
	list.push_back(newTextbody);
	string output = "Textbody added";

	lastChangedTextbody = newTextbody;

	return output;
}

string Logic::updateTextbody(string input){
	string TextbodyIndex = getFirstWord(input);
	string TextbodyInfo = removeFirstWord(input);

	unsigned int index;
	istringstream in(TextbodyIndex);
	in >> index;

	string output;
	if (index > list.size() || index <= 0){
		output = "Textbody " + TextbodyIndex + " does not exit";
		return output;
	}
	else{
		lastCommandType = "update";
		lastChangedTextbodyIndex = index - 1;
		lastUnchangedTextbody = list[index - 1];

		list[index-1].UpdateTextbody(TextbodyInfo);

		lastChangedTextbody = list[index - 1];

		output = "Textbody " + TextbodyIndex + " updated";
		return output;
	}
}

string Logic::deleteTextbody(string input){
	unsigned int index;
	istringstream in(input);
	in >> index;

	string output;
	if (index > list.size() || index <= 0){
		output = "Textbody " + input + " does not exit";
		return output;
	}
	else{
		lastCommandType = "delete";
		lastChangedTextbodyIndex = index-1;
		lastUnchangedTextbody = list[index - 1];

		list.erase(list.begin() + index - 1);
		string output = "Textbody " + input + " deleted";
		return output;
	}
}

string Logic::search(string input){	
	if (list.empty()){
		return "Empty list";
	}
	else{
		vector<string> output;
		for (unsigned int i = 0; i < list.size(); i++){
			string _Textbodyname = (list[i]).get_TextbodyName();
			vector<string> contents = splitText(_Textbodyname);

			for (unsigned int j = 0; j < contents.size(); j++){
				if (input == contents[j]){
					ostringstream oss;
					oss << i + 1 << "." << list[i].ToString() << endl;
					string TextbodyDisplay = oss.str();
					output.push_back(TextbodyDisplay);
				}
			}
		}

		return printVector(output);
	}
}

string Logic::display(){
	if (list.empty()){
		return "Empty list";
	}
	else{
		ostringstream overallOss;
		for (unsigned int i = 0; i < list.size() - 1; i++){
			ostringstream oss;
			oss << i + 1 << ". " << list[i].ToString() << endl;
			string TextbodyDisplay = oss.str();
			overallOss << TextbodyDisplay;
		}

		int size = list.size();
		overallOss << size << ". " << list[size - 1].ToString();
		return overallOss.str();
	}
}

string Logic::MarkDone(string input){
	int index;
	istringstream in(input);
	in >> index;

	lastCommandType = "done";
	lastChangedTextbodyIndex = index-1;

	list[index-1].MarkDone();
	string output = "Textbody " + input + " marked as done";
	return output;
}

string Logic::undo(){
	if (lastCommandType == "add"){
		list.pop_back();
		return "Adding command is undone";
	}
	else if (lastCommandType == "update"){
		list[lastChangedTextbodyIndex] = lastUnchangedTextbody;
		return "Updating command is undone";
	}
	else if (lastCommandType == "delete"){
		list.insert(list.begin() + lastChangedTextbodyIndex, lastUnchangedTextbody);
		return "Deleting command is undone";
	}
	else if (lastCommandType == "done"){
		list[lastChangedTextbodyIndex].MarkUndone();
		return "MarkDone command is undone";
	}
	else{
		return "Previous action cannot be undo";
	}
}

string Logic::redo(){
	if (lastCommandType == "add"){
		list.push_back(lastChangedTextbody);
		return "Adding command is redone";
	}
	else if (lastCommandType == "update"){
		list[lastChangedTextbodyIndex] = lastChangedTextbody;
		return "Updating command is redone";
	}
	else if (lastCommandType == "delete"){
		list.erase(list.begin() + lastChangedTextbodyIndex);
		return "Deleting command is redone";
	}
	else if (lastCommandType == "done"){
		list[lastChangedTextbodyIndex].MarkDone();
		return "MarkDone command is redone";
	}
	else{
		return "previous action cannot be redo";
	}
}

string Logic::getFirstWord(string input)
{
	return input.substr(0, input.find(' '));
}

string Logic::removeFirstWord(string input)
{
	return input.substr(input.find_first_of(" ") + 1);
}

vector<string> Logic::splitText(string text){
	vector<string> words;
	string word;
	istringstream in(text);
	copy(istream_iterator<string>(in),
		istream_iterator<string>(),
		back_inserter<vector<string>>(words));

	return words;
}

string Logic::printVector(vector<string> output){
	ostringstream oss;
	for (unsigned int i = 0; i < output.size(); i++){
		oss << output[i];
	}
	return oss.str();
}