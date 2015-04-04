#include <windows.h>
#include <vector>
#include "Logic.h"
#include "ShowDailyTask.h"
#include <algorithm>

vector<string> ShowDailyTask::freeSlot;

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

void printCheckVector (vector <string> freeSlot) {
	for (unsigned int i = 0;i < freeSlot.size() && !freeSlot[i].empty();i++) {
		cout<< freeSlot[i];
	}

	return;

}



vector <string> checkFreeSlot (vector <int> taskIndex) {
		cout<<"hahas"<<endl;
		vector<Task> temp = Logic::history.getVectorTextStorage();
		vector<string> tempfreeSlot;
		
		int dayStartingHour=0;
		int dayStartintMin=0;
		int dayEndingHour=24;
		int dayEndingMin=00;
		
		
		int defaultStartingHour=0;
		int defaultStartingMin=0;
		int currentEndingHour;
		int currentEndingMin;

		for (unsigned int i=0;i<taskIndex.size();i++) {
			currentEndingHour=temp[i].getStartHour();
			currentEndingMin=temp[i].getStartMinute();
			ostringstream oss;
			oss<< "free slot: " <<i+1<<". from "<< defaultStartingHour<<":"<<defaultStartingMin;
			oss<<" to "<< currentEndingHour<<":"<<currentEndingMin<<endl;
			tempfreeSlot.push_back(oss.str());
			defaultStartingHour=temp[i].getEndHour();
			defaultStartingMin=temp[i].getEndMinute();
		}
			currentEndingHour=temp[taskIndex.size()-1].getStartHour();
			currentEndingMin=temp[taskIndex.size()-1].getStartMinute();
			
			if ((currentEndingHour==dayEndingHour)&&(currentEndingMin==dayEndingMin)){
				printCheckVector(tempfreeSlot);
				return tempfreeSlot;
			} else {

			ostringstream oss;
			oss<< "free slot: " <<taskIndex.size()<<". from "<< defaultStartingHour<<":"<<defaultStartingMin;
			oss<<" to "<< dayEndingHour<<":"<<dayEndingMin<<endl;
			tempfreeSlot.push_back(oss.str());
			printCheckVector(tempfreeSlot);
			return tempfreeSlot;
}
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
	string secondCommand=Logic::getFirstWord(userMessage);
	cout<<"second: "<<secondCommand<<endl;

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
	}  else {
		//covert to mmdd
		//get into
		size_t get_date=userMessage.find("/");
		if (get_date!=string::npos) {
		currentMonth=atoi(userMessage.substr(get_date+1,2).c_str());
		currentDay=atoi(userMessage.substr(get_date-2,2).c_str());
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
			return "That day is a free day";
	} else if (secondCommand=="free") {
		
		 ShowDailyTask::freeSlot=checkFreeSlot(taskIndex);
		return "free slot shown";
	}
	else{
			return ShowTask(taskIndex).c_str();
	}
}
