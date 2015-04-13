//@author A0115365J

#include "History.h"
#include "LogicController.h"

History::History(void) {

}

History::~History(void) {

}

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
	backUpStorage=textStorage;
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
	backUpStorage=textStorage;
	textStorage=sample;
	

}
vector <Task> History::getBackUpStorage() {
	return backUpStorage;
}
/*
string History::printToString() {
	ostringstream totalTask;
	for (unsigned int i=0;i<StorageDatabase::taskHistory.getVectorTextStorage().size();i++) {
		ostringstream oss;
		Task temp=StorageDatabase::taskHistory.getVectorTextStorage()[i];
		string taskName=temp.getTaskName();
		string taskType=temp.getTaskType();
		
		if (taskType == "deadline"){
			string deadlineDate= temp.getDeadlineDate();
			string deadlineTime= temp.getDeadlineTime();
			string deadlineVenue=temp.getVenue();
			string status=temp.getStatus();
			oss<< taskName <<" "<<deadlineDate<<" "<<deadlineTime<<" "<<deadlineVenue<<" "<<endl;
			string TaskDisplay = oss.str();
			totalTask << TaskDisplay;
	}
		else if (taskType == "timed"){
			string scheduledDate=temp.getScheduledStartDate();
			string startTime=temp.getStartTime();
			string endTime=temp.getEndTime();
			string venue=temp.getVenue();
			string status=temp.getStatus();
			oss<< taskName <<" "<< scheduledDate <<" "<<startTime<<" "<<endTime<<" "<<venue<<" "<<status<<endl;
			string TaskDisplay = oss.str();
			totalTask << TaskDisplay;
	}
		else if (taskType == "floating"){
			string venue=temp.getVenue();
			string status=temp.getStatus();
			oss<< taskName<<" "<<venue<<" "<<status<<endl;
			string TaskDisplay = oss.str();
			totalTask << TaskDisplay;
	}
	}

	return totalTask.str();
}
*/