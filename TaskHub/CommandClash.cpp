#include "CommandClash.h"

const string MESSAGE_CLASH = " clashes with existing tasks";
const string MESSAGE_DOES_NOT_CLASH = " does not clash with existing tasks";

bool CommandClash::isTwoClash(int startTime1, int endTime1,int startTime2, int endTime2 ) {
	return !(startTime2>=endTime1 || startTime1>=endTime2);
}

vector<Task> CommandClash::getDayTasks(vector<Task> allTask,int day, int month) {
	vector<Task> dayTask;
	for (unsigned int i=0;i<allTask.size();i++) {
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
	

	if(scheduled_date!=string::npos) {
		Task temp1(input);
		temp = temp1;
		_startTime=temp.getStartHour()*100+temp.getStartMinute();
		_endTime=temp.getEndHour()*100+temp.getEndMinute();
		day=temp.getIntegerDay();
		month=temp.getIntegerMonth();
	}
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
		_startTime=temp.getStartHour()*100+temp.getStartMinute();
		_endTime=temp.getEndHour()*100+temp.getEndMinute();
		day=temp.getIntegerDay();
		month=temp.getIntegerMonth();
	}

	bool clash=false;

	temporary=getDayTasks(temporary,day,month);
	
	for (unsigned int i=0;i<temporary.size() && !clash;i++) {
		
		clash=isTwoClash(temporary[i].getStartHour()*100+temporary[i].getStartMinute(), temporary[i].getEndHour()*100+temporary[i].getEndMinute(), _startTime,_endTime);
	}
	
	if(clash) {
		return input + MESSAGE_CLASH ;
	}
	else {
		return input + MESSAGE_DOES_NOT_CLASH;
	}
}