#include <sstream>
#include <fstream>
#include <string>
#include "Logic.h"
#include "CommandAdd.h"
#include "CommandUpdate.h"
#include "CommandDelete.h"
#include "CommandSearch.h"
#include "CommandDisplay.h"
#include "CommandMarkDone.h"
#include "CommandMarkUncomplete.h"
#include "CommandUndo.h"
#include "CommandRedo.h"
#include "ShowDailyTask.h"
#include "CommandClear.h"
#include "CommandAutoSort.h"
#include "CommandRecurring.h"


const string CommandRecurring::COMMAND_TYPE="recurring";
const string CommandRecurring::MESSAGE_RECURRING_TASK_SET="Recurring tasks have been set";
const string EMPTY_SPACE=" ";

string CommandRecurring::setRecurringTask(string input) {

	size_t get_Start_Time;
	size_t get_Start_Date;
	size_t get_End_Time;
	size_t get_End_Date;
	size_t get_Venue;
	size_t get_TaskName;

	get_Start_Date=input.find_first_of("/");
	get_End_Date=input.find_last_of("/");
	get_Start_Time=input.find_first_of(":");
	get_End_Time=input.find_last_of(":");
	get_Venue=input.find("@");
	get_TaskName=input.find_first_of("/")-3;

	string taskName=input.substr(0,get_TaskName);
	string startingDate=input.substr(get_Start_Date-2,5);
	string startingTime=input.substr(get_Start_Time-2,5);
	string endingTime=input.substr(get_End_Time-2,5);
	
	/*
	string startingDayString=input.substr(get_Start_Date-2,2);
	string startingMonthString=input.substr(get_Start_Date+1,2);
	string endingDayString=input.substr(get_End_Date-2,2);
	string endingMonthString=input.substr(get_End_Date+1,2);
	string startingHourString=input.substr(get_Start_Time-2,2);
	string startingMinuteString=input.substr(get_Start_Time+1,2);
	string endingHourString=input.substr(get_End_Time-2,2);
	string endingMinutStringe=input.substr(get_End_Time+1,2);*/

	int startingDay=atoi(input.substr(get_Start_Date-2,2).c_str());
	int startingMonth=atoi(input.substr(get_Start_Date+1,2).c_str());
	int endingDay=atoi(input.substr(get_End_Date-2,2).c_str());
	int endingMonth=atoi(input.substr(get_End_Date+1,2).c_str());
	int startingHour=atoi(input.substr(get_Start_Time-2,2).c_str());
	int startingMinute=atoi(input.substr(get_Start_Time+1,2).c_str());;
	int endingHour=atoi(input.substr(get_End_Time-2,2).c_str());
	int endingMinute=atoi(input.substr(get_End_Time+1,2).c_str());;
	string venue="";
	for (int i=startingDay;i<=endingDay;i++) {
		char taskname[256];
		strcpy_s(taskname, taskName.c_str());
		string message=taskname+EMPTY_SPACE+" -from "+startingTime+" -to "+endingTime+" "+to_string(i)+"/"+to_string(endingMonth);
		CommandAdd::addMessage(message);

	}
	return MESSAGE_RECURRING_TASK_SET;
}