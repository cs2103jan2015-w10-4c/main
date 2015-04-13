//@author A0115365J

#include <algorithm> 
#include "CommandAutoSort.h"

const int MAX_TIME_LENGTH = 14;		//for yyyymmddhhmm
const string CommandAutoSort::STATUS_DONE = "done";
const string CommandAutoSort::STATUS_UNCOMPLETED = "uncompleted";
const string CommandAutoSort::STATUS_FLOATING = "floating";
const string CommandAutoSort::MESSAGE_SORT_SUCCESSFUL = "sort successful";
const char CommandAutoSort::NULL_TERMINATION_CHARACTER = '\0';

CommandAutoSort::CommandAutoSort () {
}

CommandAutoSort::~CommandAutoSort () {

}

bool CommandAutoSort::compareCriteria(Task firstTask, Task secondTask) {

	//uncompleted tasks sorted after done / undo tasks
	if((firstTask.getStatus() == STATUS_UNCOMPLETED) && (secondTask.getStatus() != STATUS_UNCOMPLETED)){                          
		return false;
	} else if ((firstTask.getStatus() != STATUS_UNCOMPLETED) && (secondTask.getStatus() == STATUS_UNCOMPLETED)){
		return true;
	} else if ((firstTask.getStatus() == STATUS_UNCOMPLETED) && (secondTask.getStatus()) == STATUS_UNCOMPLETED){
		return false;
	} else if((firstTask.getStatus() != STATUS_UNCOMPLETED) && (secondTask.getStatus() != STATUS_UNCOMPLETED)){
	
	
	//done tasks sorted after undone tasks
	if((firstTask.getStatus() == STATUS_DONE) && (secondTask.getStatus() != STATUS_DONE)){                          
		return false;
	} else if ((firstTask.getStatus() != STATUS_DONE) && (secondTask.getStatus() == STATUS_DONE)){
		return true;
	} else if ((firstTask.getStatus() == STATUS_DONE) && (secondTask.getStatus()) == STATUS_DONE){
		return false;
	} else if((firstTask.getStatus() != STATUS_DONE) && (secondTask.getStatus() != STATUS_DONE)){

		//for undone tasks
		//floating tasks sorted after timed and deadline tasks
		if((firstTask.getTaskType() == STATUS_FLOATING) && (secondTask.getTaskType() != STATUS_FLOATING)){                //floating sorted after timed
			return false;															
		} else if ((firstTask.getTaskType() != STATUS_FLOATING) && (secondTask.getTaskType() == STATUS_FLOATING)){
			return true;
		} else if ((firstTask.getTaskType() == STATUS_FLOATING) && (secondTask.getTaskType() == STATUS_FLOATING)){
			return false;
		} else if((firstTask.getTaskType() != STATUS_FLOATING) && (secondTask.getTaskType() != STATUS_FLOATING)){
			
			//for timed and deadline tasks
			//they are sorted by time, where the start time a timed task is used
			char firstTaskTime[MAX_TIME_LENGTH];
			char secondTaskTime[MAX_TIME_LENGTH];

			sprintf_s(firstTaskTime, (firstTask.getScheduledDateReverse() + firstTask.getStartTime()).c_str());
			sprintf_s(secondTaskTime, (secondTask.getScheduledDateReverse() + secondTask.getStartTime()).c_str());

			int i = 0;
			while(firstTaskTime[i] != NULL_TERMINATION_CHARACTER){
				while(secondTaskTime[i] != NULL_TERMINATION_CHARACTER){
					if(firstTaskTime[i] < secondTaskTime[i]){
						return true;
					} else if(firstTaskTime[i] > secondTaskTime[i]){
						return false;
					}
					i++;
				}
				return false;
			}
			return false;
		}
	}
	return false;
}
	return false;
}

string CommandAutoSort::autoSort () {
	
	vector<Task> temporary = StorageDatabase::taskHistory.getVectorTextStorage();

	stable_sort(temporary.begin(),temporary.end(),CommandAutoSort::compareCriteria);

	StorageDatabase::taskHistory.setVectorTextStorage(temporary);
	
	return MESSAGE_SORT_SUCCESSFUL;

}