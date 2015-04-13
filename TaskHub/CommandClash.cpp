//@author A0115793Y
#include "CommandClash.h"

const string MESSAGE_CLASH = " clashes with existing tasks";
const string MESSAGE_DOES_NOT_CLASH = " does not clash with existing tasks";
const int START_OF_FOR_LOOP = 0;
const int TIME_CONVERSION_FACTOR = 100;

bool CommandClash::isTwoClash(int startTime1, int endTime1,int startTime2, int endTime2 ) {
	return !(startTime2>=endTime1 || startTime1>=endTime2);
}

vector<Task> CommandClash::getDayTasks(vector<Task> allTask,int day, int month) {
	vector<Task> dayTask;
	for (unsigned int i=START_OF_FOR_LOOP;i<allTask.size();i++) {
		if (month==allTask[i].getIntegerMonth()) {
			if (day==allTask[i].getIntegerDay()) {
				dayTask.push_back(allTask[i]);
			}
		}
	}
	return dayTask;
}
string CommandClash::clash(string input) {
	vector<Task> temporary = StorageDatabase::taskHistory.getVectorTextStorage();
	size_t scheduled_date = input.find("/");
	Task temp;
	int _endTime;
	int _startTime;
	int day,month;
	
	//If user indicate date, set the date as required by the user
	if(scheduled_date!=string::npos) {
		Task temp1(input);
		temp = temp1;
		_startTime=temp.getStartHour()*TIME_CONVERSION_FACTOR+temp.getStartMinute();
		_endTime=temp.getEndHour()*TIME_CONVERSION_FACTOR+temp.getEndMinute();
		day=temp.getIntegerDay();
		month=temp.getIntegerMonth();
	}
	//If user never indicate date, by default the date is today's date
	else {
		SYSTEMTIME lt;
		localTime timeNow;
		GetLocalTime(&lt);
  
		timeNow._day=lt.wDay;
		timeNow._mon=lt.wMonth;
		day=timeNow._day;
		month=timeNow._mon;
		
		Task temp1(input+to_string(day)+"/"+to_string(month));
		temp = temp1;
		_startTime=temp.getStartHour()*TIME_CONVERSION_FACTOR+temp.getStartMinute();
		_endTime=temp.getEndHour()*TIME_CONVERSION_FACTOR+temp.getEndMinute();
		day=temp.getIntegerDay();
		month=temp.getIntegerMonth();
	}

	//Retrieve all tasks on the selected date from storage
	temporary=getDayTasks(temporary,day,month);
	
	//Check whether the input time perieod clashes with the existing tasks
	bool clash=false;
	for (unsigned int i=START_OF_FOR_LOOP;i<temporary.size() && !clash;i++) {
		
		clash=isTwoClash(temporary[i].getStartHour()*100+temporary[i].getStartMinute(), temporary[i].getEndHour()*100+temporary[i].getEndMinute(), _startTime,_endTime);
	}
	
	if(clash) {
		return input + MESSAGE_CLASH ;
	}
	else {
		return input + MESSAGE_DOES_NOT_CLASH;
	}
}