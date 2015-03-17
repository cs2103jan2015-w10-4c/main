#include <sstream>
#include "Logic.h"
#include "AddingMessage.h"
#include "UpdatingMessage.h"
#include "DeletingMessage.h"
#include "Search.h"
#include "DisplayMessage.h"
#include "MarkMessageDone.h"

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
	
	 return AddingMessage::addMessage(input);
}

string Logic::updateTextbody(string input){
	
	return UpdatingMessage::updateMessage(input); 
}

string Logic::deleteTextbody(string input){
	
	return deleingMessage::deleteMessage(input);
}

string Logic::search(string input){	
	
	return searchingMessage::searchMessage (input);
}

string Logic::display(){
	
	return displayingMessage::displayMessage();
}

string Logic::MarkDone(string input){
	
	return markingDoneMessage::markMessageDone(input);
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