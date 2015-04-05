#include "CommandClash.h"


bool CommandClash::isTwoClash(int startTime1, int endTime1,int startTime2, int endTime2 ){
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
	int _startTime;
	int _endTime;
	int day,month;
	_startTime=temp.getStartHour()*100+temp.getStartMinute();
	_endTime=temp.getEndHour()*100+temp.getEndMinute();
	
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
		clash=isTwoClash(temporary[i].getStartHour()*100+temporary[i].getStartMinute(), temporary[i].getEndHour()*100+temporary[i].getEndMinute(), _startTime,_endTime);
	}
	
	if(clash)
		return input + "clashes with existing tasks";
	else 
		return input + "does not clash with existing tasks";
}