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


History Logic::history;

void Logic::getStorage(){
	vector<string> Logic = StorageController::returnTask();
	for (unsigned int i = 0; i < Logic.size(); i++){
		string TaskString = removeFirstWord(Logic[i]);
		Task newTask(TaskString, "copy");
		Logic::history.setVectorTextStorage(newTask);
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

string Logic::help() {

	cout << "Some examples:\n";

	cout << "Add: add meeting -from 1200 -to 1400 25/12\n";
	cout << "Display all: display \n";
	cout << "Display Static Tasks: display static\n";
	cout << "Display Deadline Tasks: display deadline\n";
	cout << "Display Unfinished Tasks: display unfinished\n";
	cout << "Display Finished Tasks: display finished\n";
	cout << "Display Floating Tasks: display floating\n";
	
	cout << "Update: Update 1 -from 1400 -to 1500 23/12\n";
	cout << "Search: search meeting\n";
	cout << "Delete: delete 1\n";
	
	cout << "Undo: undo\n";
	cout << "Redo: redo\n";
	cout << "Exit: exit\n";

	return "";
}