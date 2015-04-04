#include <windows.h>
#include <vector>
#include "Logic.h"
#include "ShowDailyTask.h"
#include <algorithm>

vector<string> ShowDailyTask::messageDisplayed;

void ShowDailyTask::getSystemTime(localTime &timevalue) {

	SYSTEMTIME lt;
    GetLocalTime(&lt);
  
	timevalue._day=lt.wDay;
	timevalue._mon=lt.wMonth;
	timevalue._hour=lt.wHour;
	timevalue._min=lt.wMinute;

}


vector <string> ShowTask (vector <int> taskIndex) {
	
		for (unsigned int i = 0; i < taskIndex.size() ; i++){
			ostringstream oss;
			oss << i + 1 << ". " << Logic::history.getVectorTextStorage()[taskIndex[i]].ToString() << endl;
			string TaskDisplay = oss.str();
			ShowDailyTask::messageDisplayed.push_back(TaskDisplay);
			
		}
		
		return ShowDailyTask::messageDisplayed;

}



string ShowDailyTask::showDayTask (string userMessage) {

	transform(userMessage.begin(),userMessage.end(),userMessage.begin(),::tolower);
	vector<Task> temporary=Logic::history.getVectorTextStorage();
	vector<int> taskIndex;
	localTime timeNow;
	ShowDailyTask::getSystemTime(timeNow);
	int currentDay=timeNow._day;
	int currentMonth=timeNow._mon;
	int currentMinute=timeNow._min;
	int currentHour=timeNow._hour;
	int size=temporary.size();
		
	ShowDailyTask::messageDisplayed.clear();
	if (userMessage=="today") {
		
		//get into that day and display
		for (int i=0;i<size;i++) {
			if (currentMonth==temporary[i].getIntegerMonth()) {
				
				if (currentDay==temporary[i].getIntegerDay()) {
					taskIndex.push_back(i);
				}
			}

		}
		
	} else if (userMessage=="tomorrow") {

		//get into that day and display
		currentDay++;
		for (int i=0;i<size;i++) {
			if (currentMonth==temporary[i].getIntegerMonth()) {
				if (currentDay==temporary[i].getIntegerDay()) {
					taskIndex.push_back(i);
				}
			}

		}
	} else if (userMessage=="now") {

		//get into that day and display
		
		for (int i=0;i<size;i++) {
			if (currentMonth==temporary[i].getIntegerMonth()) {
				if (currentDay==temporary[i].getIntegerDay()) {
					if (currentHour==temporary[i].getStartHour()) {
						//if (currentMinute==temporary[i].getMinute()) {
							taskIndex.push_back(i);
						//}
					}
				}
			}
		} 
	} else if (userMessage=="free") {
		//shuyuan's code

	} else {
		//covert to mmdd
		//get into
		size_t get_date=userMessage.find("/");
		if (get_date!=string::npos) {
		currentMonth=atoi(userMessage.substr(get_date+1,2).c_str());
		currentDay=atoi(userMessage.substr(0,get_date).c_str());
		cout<<"month: "<<currentMonth<<"day: "<<currentDay<<endl;
		} 
		size_t get_time=userMessage.find(":");
		if (get_time !=string::npos) {
		currentHour=atoi(userMessage.substr(get_time-2,2).c_str());
		currentMinute=atoi(userMessage.substr(get_time+1,2).c_str());
		cout<<"hour: "<<currentHour<<"minute: "<<currentMinute<<endl;
		}
		
		if ((get_time==string::npos)&&(get_date!=string::npos)) {
			cout<<"10086"<<endl;
			for (int i=0;i<size;i++) {
				cout<<"task month: "<<temporary[i].getIntegerMonth()<<endl;
				if (currentMonth==temporary[i].getIntegerMonth()) {
					if (currentDay==temporary[i].getIntegerDay()) {
						taskIndex.push_back(i);
					}
				}
			}
		
		} //when no dates are enter, by default it is today	
		else if ((get_time!=string::npos)&&(get_date==string::npos)) {

			for (int i=0;i<size;i++) {
				if (currentMonth==temporary[i].getIntegerMonth()) {
					if (currentDay==temporary[i].getIntegerDay()) {
						if (currentHour==temporary[i].getStartHour()) {
					//if (currentMinute==temporary[i].getMinute()) {
					taskIndex.push_back(i);
					//}
						}
					}
				}
			}
		} else if ((get_time!=string::npos)&&(get_date!=string::npos)) {
			for (int i=0;i<size;i++) {
				if (currentMonth==temporary[i].getIntegerMonth()) {
					if (currentDay==temporary[i].getIntegerDay()) {
						if (currentHour==temporary[i].getStartHour()) {
					//if (currentMinute==temporary[i].getMinute()) {
						taskIndex.push_back(i);
					//}
						}
					}
				}
			}
		}
	}

	if (taskIndex.empty()) {
			return "Nothing found on that day";
		} else {
			return "Task is shown";
	}
}