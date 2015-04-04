#include "CommandClash.h"


bool CommandClash::isTwoClash(string startTime1, string endTime1,string startTime2, string endTime2 ){
	return !(startTime2>=endTime1 || startTime1>=endTime2);
}
vector<Task> getDayTask(vector<Task> allTask,int day, int month){
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
string CommandClash::Clash(string input){
	vector<Task> temporary = Logic::history.getVectorTextStorage();
	Task temp(input);
	bool clash=false;
	string _startTime, _endTime;
	int day,month;
	_startTime=temp.getStartTime();
	_endTime=temp.getEndTime();
	
	size_t scheduled_date = input.find_first_of("/");
	if(scheduled_date!=string::npos){
		day=temp.getIntegerDay();
		month=temp.getIntegerMonth();
	}
	else{
		SYSTEMTIME lt;
		localTime timeNow;
		GetLocalTime(&lt);
  
		timeNow._day=lt.wDay;
		timeNow._mon=lt.wMonth;
		day=timeNow._day;
		month=timeNow._mon;
	}

	temporary=getDayTask(temporary,day,month);

	for (unsigned int i=0;i<temporary.size() && !clash;i++) {
		clash=isTwoClash(temporary[i].getStartTime(), temporary[i].getEndTime(), _startTime,_endTime);
	}
	
	if(clash)
		return input + "clashes with existing tasks";
	else 
		return input + "does not clash with existing tasks";
}