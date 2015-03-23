#include "History.h"

History::History(void) {

}

History::~History(void) {}

void History::setLastChangedTaskIndex( int index) {

	lastChangedTaskIndex= index-1;
}

void History::setLastChangedTask(Task changedTask) {

	lastChangedTask=changedTask;
}

void History::setLastCommandType(string changedCommandType) {

	lastCommandType=changedCommandType;
}

void History::setLastUnchangedTask(Task unChangedTask) {

	lastUnchangedTask=unChangedTask;
}

void History::setVectorTextStorage (Task taskString) {

	textStorage.push_back(taskString);
}

int History::getLastChangedTaskIndex() {

	return lastChangedTaskIndex;
}

Task History::getLastChangedTask() {
	return lastChangedTask;
}

Task History::getLastUnchangedTask() {
	return lastUnchangedTask;
}

vector<Task> History::getVectorTextStorage() {
	
	return textStorage;
}

string History::getLastCommandType() {
	return lastCommandType;
}

void History::setVectorTextStorage(vector<Task> sample) {

	textStorage=sample;

}