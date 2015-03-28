#include <windows.h>
#include <vector>
#include "Logic.h"
#include "ShowDailyTask.h"
#include <algorithm>

void ShowDailyTask::getSystemTime(localTime &timevalue) {

	SYSTEMTIME lt;
    GetLocalTime(&lt);
  
	timevalue._day=lt.wDay;
	timevalue._mon=lt.wMonth;
	timevalue._hour=lt.wHour;
	timevalue._min=lt.wMinute;

}


string ShowTask (vector <int> taskIndex) {
	ostringstream totalTask;
		for (unsigned int i = 0; i < taskIndex.size() ; i++){
			ostringstream oss;
			oss << i + 1 << ". " << Logic::history.getVectorTextStorage()[taskIndex[i]].ToString() << endl;
			string TaskDisplay = oss.str();
			totalTask << TaskDisplay;
		}
		
		return totalTask.str();


}



string ShowDailyTask::showDayTask (string userMessage) {

	transform(userMessage.begin(),userMessage.end(),userMessage.begin(),::tolower);
	vector<Task> temporary=Logic::history.getVectorTextStorage();

	if (userMessage=="today") {
		
		//get into that day and display
		localTime timeNow;
		ShowDailyTask::getSystemTime(timeNow);
		int currentDay=timeNow._day;
		int currentMonth=timeNow._mon;
		int size=temporary.size();
		vector<int> taskIndex;
		for (int i=0;i<size;i++) {
			if (currentMonth==temporary[i].getIntegerMonth()) {
				if (currentDay==temporary[i].getIntegerDay()) {
					taskIndex.push_back(i);
				}
			}

		}
		
		return ShowTask(taskIndex).c_str();

	} else if (userMessage=="tomorrow") {

		//get into that day and display
		localTime timeNow;
		ShowDailyTask::getSystemTime(timeNow);
		int currentDay=timeNow._day+1;
		int currentMonth=timeNow._mon;
		int size=temporary.size();
		vector<int> taskIndex;
		for (int i=0;i<size;i++) {
			if (currentMonth==temporary[i].getIntegerMonth()) {
				if (currentDay==temporary[i].getIntegerDay()) {
					taskIndex.push_back(i);
				}
			}

		}
		
		return ShowTask(taskIndex).c_str();
	} else {
		//covert to mmdd
		//get into
		return "";

	}
	
}