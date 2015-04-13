//@author A0115365J

#include <windows.h>
#include <vector>
#include <algorithm>
#include "LogicController.h"
#include "ShowDailyTask.h"

const string ShowDailyTask::MESSAGE_TODAY = "today";
const string ShowDailyTask::MESSAGE_SHOW = "show";
const string ShowDailyTask::MESSAGE_TOMORROW = "tomorrow";
const string ShowDailyTask::MESSAGE_SECOND_COMMAND = "free";
const string ShowDailyTask::MESSAGE_NOW = "now";
const string ShowDailyTask::MESSAGE_EMPTY = "Nothing found on that day";
const string ShowDailyTask::MESSAGE_FREE_SLOT_SHOWN = "free slot shown";
const string ShowDailyTask::MESSAGE_TASK_SHOWN = "Task is shown";

vector<string> ShowDailyTask::messageDisplayed;

ShowDailyTask::ShowDailyTask () {

}

ShowDailyTask::~ShowDailyTask () {

}

void ShowDailyTask::getSystemTime(localTime &timevalue) {

	SYSTEMTIME lt;
    GetLocalTime(&lt);
  
	timevalue._day = lt.wDay;
	timevalue._mon = lt.wMonth;
	timevalue._hour = lt.wHour;
	timevalue._min = lt.wMinute;

}


vector <string> ShowDailyTask::ShowTask (vector <int> taskIndex) {
		
		for (unsigned int i = 0; i < taskIndex.size() ; i++){
			ostringstream oss;
			oss << taskIndex[i] + 1 << ". " << StorageDatabase::taskHistory.getVectorTextStorage()[taskIndex[i]].ToString() << endl;
			string TaskDisplay = oss.str();
			ShowDailyTask::messageDisplayed.push_back(TaskDisplay);
			
			
		}
		
		return ShowDailyTask::messageDisplayed;

}

vector <string> ShowDailyTask::checkFreeSlot (vector <int> taskIndex) {
		
		vector<Task> temp = StorageDatabase::taskHistory.getVectorTextStorage();
		vector<string> tempfreeSlot;
		
		int dayStartingHour = 0;
		int dayStartintMin = 0;
		int dayEndingHour = 24;
		int dayEndingMin = 00;
		int defaultStartingHour = 0;
		int defaultStartingMin = 0;
		int currentEndingHour;
		int currentEndingMin;

		for (unsigned int i = 0;i < taskIndex.size(); i++) {
			currentEndingHour = temp[taskIndex[i]].getStartHour();
			currentEndingMin = temp[taskIndex[i]].getStartMinute();
			ostringstream oss;
			oss<< "free slot: " << i + 1 <<". from "<< defaultStartingHour<<":"<< defaultStartingMin;
			oss<<" to "<< currentEndingHour <<":"<< currentEndingMin <<endl;
			tempfreeSlot.push_back(oss.str());
			defaultStartingHour = temp[taskIndex[i]].getEndHour();
			defaultStartingMin = temp[taskIndex[i]].getEndMinute();
		}
			currentEndingHour = temp[taskIndex.back()].getEndHour();
			currentEndingMin = temp[taskIndex.back()].getEndMinute();
			
			
			if ((currentEndingHour == dayEndingHour)&&(currentEndingMin == dayEndingMin)){
				return tempfreeSlot;
			} else {

			ostringstream oss;
			oss<< "free slot: " <<taskIndex.size() + 1 <<". from "<< currentEndingHour <<":"<<currentEndingMin;
			oss<<" to "<< dayEndingHour <<":"<< dayEndingMin <<endl;
			tempfreeSlot.push_back(oss.str());
			return tempfreeSlot;
}
}

void ShowDailyTask::getDayTask (vector <Task> & temporary, vector <int> &taskIndex, int currentMonth, int currentDay) {
	int size = temporary.size();
	if (!temporary.empty()) {
		for ( int i = 0; i < size; i++) {
			if (currentMonth == temporary[i].getIntegerMonth()) {
				
				if (currentDay == temporary[i].getIntegerDay()) {
					
					taskIndex.push_back(i);
				}
			}

		}
		}
}

void ShowDailyTask::getHourTask (vector <Task> &temporary, vector <int> &taskIndex, int currentMonth, int currentDay, int currentHour) {
	int size = temporary.size();
	if (!temporary.empty()) {
	for (int i = 0; i < size; i++) {
			if (currentMonth == temporary[i].getIntegerMonth()) {
				if (currentDay == temporary[i].getIntegerDay()) {
					if (currentHour == temporary[i].getStartHour()) {
							taskIndex.push_back(i);
					}
				}
			}
		}
	}
}

string ShowDailyTask::showDayTask (string userMessage) {

	transform(userMessage.begin(),userMessage.end(),userMessage.begin(),::tolower);
	vector<Task> temporary = StorageDatabase::taskHistory.getVectorTextStorage();
	
	vector<int> taskIndex;
	localTime timeNow;
	ShowDailyTask::getSystemTime(timeNow);

	int currentDay = timeNow._day;
	int currentMonth = timeNow._mon;
	int currentMinute = timeNow._min;
	int currentHour = timeNow._hour;
	int size = temporary.size();

	string secondCommand = Logic::getFirstWord(userMessage);
	ShowDailyTask::messageDisplayed.clear();

	if (userMessage == MESSAGE_TODAY || userMessage == MESSAGE_SHOW) {
		//get into that day and display
		getDayTask(temporary, taskIndex, currentMonth, currentDay);
		
	} else if (userMessage == MESSAGE_TOMORROW) {
		//get into that day and display
		currentDay++;
		getDayTask(temporary, taskIndex, currentMonth, currentDay);

	} else if (userMessage == MESSAGE_NOW) {

		//get into that hour and display
		getHourTask (temporary, taskIndex, currentMonth, currentDay, currentHour);

	} else {
		size_t get_date = userMessage.find("/");
		
		if (get_date != string::npos) {
			userMessage= " "+userMessage;
			DateParser getDate (userMessage);
			currentMonth = getDate.getMonth();
			currentDay = getDate.getDay();
		
		} //try date parser
		/*
		currentMonth = atoi(userMessage.substr(get_date+1,2).c_str());
		currentDay = atoi(userMessage.substr(get_date-2,2).c_str());
		*/
		size_t get_time = userMessage.find(":");
		if (get_time != string::npos) {
			
			userMessage= " "+userMessage;
			TimeParser getTime(userMessage);
			currentHour = getTime.getStartHour();
			currentMinute = getTime.getStartMinute();

		//currentHour = atoi(userMessage.substr(get_time-2,2).c_str());
		//currentMinute = atoi(userMessage.substr(get_time+1,2).c_str());
		} //try time parser
		
		if ((get_time == string::npos)&&(get_date != string::npos)) {
			//show a particular day tasks
			getDayTask(temporary, taskIndex, currentMonth, currentDay);
		
		} //when no dates are enter, by default it is today	
		else if ((get_time != string::npos)&&(get_date == string::npos)) {
			getHourTask (temporary, taskIndex, currentMonth, currentDay, currentHour);

		} else if ((get_time != string::npos)&&(get_date != string::npos)) {
			//show tasks of a particular time on a particular day
			getHourTask (temporary, taskIndex, currentMonth, currentDay, currentHour);
		}
	}

	if (taskIndex.empty()) {
		return MESSAGE_EMPTY;

	} else if (secondCommand == MESSAGE_SECOND_COMMAND) {
			ShowDailyTask::messageDisplayed = checkFreeSlot(taskIndex);
			return MESSAGE_FREE_SLOT_SHOWN;
	}
	else {
		ShowTask(taskIndex);	
		return MESSAGE_TASK_SHOWN;
	}
}