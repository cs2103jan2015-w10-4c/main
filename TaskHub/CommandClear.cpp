#include "CommandClear.h"
#include "CommandDelete.h"

const string CommandClear::MESSAGE_CLEAR_ALL="All messages have been clear";
const string CommandClear::MESSAGE_CLEAR_FROM_TO="Message with index from %s to %s have been clear";
const string CommandClear::MESSAGE_CLEAR_ERROR="Invalid Task Index";
const string CommandClear::MESSAGE_CLEAR_DONE="All the done tasks have been removed";
const string CommandClear::MESSAGE_CLEAR_UNCOMPLETED="All the uncompleted tasks have been removed";

string CommandClear::clearTask(string input) {

	vector <Task> temporary=Logic::history.getVectorTextStorage();

	transform(input.begin(),input.end(),input.begin(),::tolower);

	if (input=="all"||input=="clear") {// when just clear is entered, by default is to clear all
		
		temporary.clear();
		Logic::history.setVectorTextStorage(temporary);
		sprintf_s(Logic::messageDisplayed, MESSAGE_CLEAR_ALL.c_str());

	} else if (input=="done") {
		
		for (unsigned int i=0;i<temporary.size();i++) {
			if (temporary[i].getStatus()=="done") {
				string s=to_string(i+1);
				s=CommandDelete::deleteMessage(s);
			}
		}
		sprintf_s(Logic::messageDisplayed, MESSAGE_CLEAR_DONE.c_str());

	} else if (input=="uncompleted") {
		
		for (unsigned int i=0;i<temporary.size();i++) {
			if (temporary[i].getStatus()=="uncompleted") {
				string s=to_string(i+1);
				s=CommandDelete::deleteMessage(s);
			}
		}
		sprintf_s(Logic::messageDisplayed, MESSAGE_CLEAR_UNCOMPLETED.c_str());
	} else { // delete continuously
		size_t get_task_index=input.find("-");
		if (get_task_index!=string::npos) {
			unsigned int endIndex=atoi(input.substr(get_task_index+1,2).c_str());
			unsigned int beginIndex=atoi(input.substr(0,get_task_index).c_str());
			cout<<"begin: "<<beginIndex<< "  end: "<<endIndex<<endl;
			if ((beginIndex>=0) && (beginIndex < temporary.size()) && (endIndex>=beginIndex) && (endIndex<temporary.size())) {
				
				vector<Task>::iterator itr = temporary.begin()+beginIndex-1;
				temporary.erase(itr,itr+endIndex-beginIndex+1);
				Logic::history.setVectorTextStorage(temporary);
				sprintf_s(Logic::messageDisplayed,MESSAGE_CLEAR_FROM_TO.c_str(),input.substr(0,get_task_index).c_str(),input.substr(get_task_index+1,2).c_str());
				
			} else {
			
				sprintf_s(Logic::messageDisplayed,MESSAGE_CLEAR_ERROR.c_str());
			}
		} else {
			sprintf_s(Logic::messageDisplayed,MESSAGE_CLEAR_ERROR.c_str());
		}
	}
	return Logic::messageDisplayed;
}