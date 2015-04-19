//@author A0115365J
#include <sstream>
#include <fstream>
#include "LogicController.h"
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
#include "CommandAutoSort.h"
#include "CommandRecurring.h"
#include "CommandClash.h"
#include "CommandDetail.h"

char Logic::messageDisplayed[MAX_BUFFERRING_CAPACITY] = "";

void Logic::getStorage(){//@author A0115365J-reused
	vector<string> Logic = StorageController::returnTask();
	for (unsigned int i = 0; i < Logic.size(); i++){
		string TaskString = removeFirstWord(Logic[i]);
		Task newTask(TaskString, "regain");
		StorageDatabase::taskHistory.setVectorTextStorage(newTask);
	}
	
}

//@author A0115365J
string Logic::getDetail (string input) {

	string temp = CommandDetail::detailMessage(input);
	return CommandDetail::FEEDBACK_SYSTEM;
}

string Logic::addTask(string input){
	
	 return CommandAdd::addOperation(input);
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
string Logic::recurTask (string input) {

	return CommandRecurring::setRecurringTask(input);
}
string Logic::sort () {
	return CommandAutoSort::autoSort();
}

string Logic::checkClash(string input) {
	return CommandClash::clash(input);
}
//@author A0115365J-reused
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

	cout << "Add: add meeting -from 12:00 -to 14:00 25/12\n";
	cout << "Display all: display or display all\n";
	cout << "Display timed Tasks: display timed\n";
	cout << "Display Deadline Tasks: display deadline\n";
	cout << "Display Unfinished Tasks: display uncompleted\n";
	cout << "Display Finished Tasks: display done\n";
	cout << "Display Floating Tasks: display floating\n";
	cout <<  "Show today task: show today"<<endl;
	cout << "Show today tomorrow: show tomorrow"<<endl;
	cout << "Show today now: show now"<<endl;
	cout << "Show task on a paticular date: show 12/12 (dd/mm)"<<endl;
	cout << "search task: search cs meeting\n";
	cout << "mark task completed: done 1\n";
	cout << "mark task uncompleted: uncomplete 1\n";
	cout << "clear all tasks: clear all or clear\n";
	cout << "clear timed tasks: clear timed\n";
	cout << "clear done: clear done\n";
	cout << "clear uncompleted tasks: clear uncompleted\n";
	cout << "clear tasks continuously: clear 1-10\n";
	cout << "Update: Update 1 -from 14:00 -to 15:00 23/12\n";
	cout << "Search: search meeting\n";
	cout << "Delete: delete 1\n";
	
	cout << "Undo: undo\n";
	cout << "Redo: redo\n";
	cout << "Exit: exit\n";

	return "";
}