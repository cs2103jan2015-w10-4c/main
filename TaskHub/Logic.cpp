#include <sstream>
#include <fstream>
#include "Logic.h"
#include "CommandAdd.h"
#include "CommandUpdate.h"
#include "CommandDelete.h"
#include "CommandSearch.h"
#include "CommandDisplay.h"
#include "CommandMarkDone.h"
#include "CommandMarkUncomplete.h"
#include "CommandUndo.h"
#include "CommandRedo.h"
#include "ShowDailyTask.h"
#include "CommandClear.h"

char Logic::messageDisplayed[MAX_BUFFERRING_CAPACITY]="";

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
	
	return CommandUpdate::updateMessage(input); 
}

string Logic::deleteTask(string input){
	
	return CommandDelete::deleteMessage(input);
}

string Logic::search(string input){	
	
	return CommandSearch::searchMessage (input);
}

string Logic::display(string input){
	
	return CommandDisplay::display(input);
}

string Logic::MarkDone(string input){
	
	return markingDoneMessage::markMessageDone(input);
}

string Logic::markUncompleted (string input) {
	return markingMessageUncomplete::markMessageUncompleted (input);
}
string Logic::undo(){
	
	return undoChange::undo();
}

string Logic::redo(){
	
	return redoChange::redo();
}

string Logic::show(string input) {

	return ShowDailyTask::showDayTask(input);
}

string Logic::clearAll(string input) {
	return CommandClear::clearTask(input);
}

string Logic::getFirstWord(string input)
{
	return input.substr(0, input.find(' '));
}

string Logic::removeFirstWord(string input)
{
	return input.substr(input.find_first_of(" ") + 1);
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