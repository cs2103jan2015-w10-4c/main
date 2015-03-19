#include <sstream>
#include "Logic.h"
#include "CommandAdd.h"
#include "CommandUpdate.h"
#include "CommandDelete.h"
#include "CommandSearch.h"
#include "CommandDisplay.h"
#include "CommandMarkDone.h"
#include "CommandUndo.h"
#include "CommandRedo.h"

vector<Task> Logic::textStorage;
string Logic::lastCommandType;
int Logic::lastChangedTaskIndex;
Task Logic::lastChangedTask;
Task Logic::lastUnchangedTask;

void Logic::getStorage(){
	vector<string> Logic = storage::returnTask();

	for (unsigned int i = 0; i < Logic.size(); i++){
		string TaskString = removeFirstWord(Logic[i]);
		Task newTask(TaskString, "copy");
		textStorage.push_back(newTask);
	}
}

string Logic::addTask(string input){
	
	 return CommandAdd::addMessage(input);
}

string Logic::updateTask(string input){
	
	return UpdatingMessage::updateMessage(input); 
}

string Logic::deleteTask(string input){
	
	return CommandDelete::deleteMessage(input);
}

string Logic::search(string input){	
	
	return CommandSearch::searchMessage (input);
}

string Logic::display(){
	
	return CommandDisplay::display();
}

string Logic::MarkDone(string input){
	
	return markingDoneMessage::markMessageDone(input);
}

string Logic::undo(){
	
	return undoChange::undo();
}

string Logic::redo(){
	
	return redoChange::redo();
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