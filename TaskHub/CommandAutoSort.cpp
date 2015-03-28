#include "CommandAutoSort.h"

const int MAX_TIME_LENGTH = 14;		//for mmddhhmm


bool compareCriteria(Task firstTask, Task secondTask) {

	//done tasks sorted after undone tasks
	if((firstTask.getStatus()=="done") && (secondTask.getStatus()!="done")){                          
		return false;
	} else if ((firstTask.getStatus()!="done") && (secondTask.getStatus()=="done")){
		return true;
	} else if ((firstTask.getStatus()=="done") && (secondTask.getStatus())=="done"){
		return false;
	} else if((firstTask.getStatus()!="done") && (secondTask.getStatus()!="done")){

		//for undone tasks
		//floating tasks sorted after timed and deadline tasks
		if((firstTask.getTaskType() =="floating") && (secondTask.getTaskType() !="floating")){                //floating sorted after timed
			return false;															
		} else if ((firstTask.getTaskType() != "floating") && (secondTask.getTaskType() == "floating")){
			return true;
		} else if ((firstTask.getTaskType() == "floating") && (secondTask.getTaskType() == "floating")){
			return false;
		} else if((firstTask.getTaskType() != "floating") && (secondTask.getTaskType() != "floating")){
			
			//for timed and deadline tasks
			//they are sorted by time, where the start time a timed task is used
			char firstTaskTime[MAX_TIME_LENGTH];
			char secondTaskTime[MAX_TIME_LENGTH];

			sprintf_s(firstTaskTime, (firstTask.getScheduledDate() + firstTask.getStartTime()).c_str());
			sprintf_s(secondTaskTime, (secondTask.getScheduledDate() + secondTask.getStartTime()).c_str());

			int i = 0;
			while(firstTaskTime[i] != '\0'){
				while(secondTaskTime[i] != '\0'){
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



void CommandAutoSort::autoSort () {
	
	vector<Task> temporary=Logic::history.getVectorTextStorage();

	stable_sort(temporary.begin(),temporary.end(),compareCriteria);

	Logic::history.setVectorTextStorage(temporary);
	
	return;

}