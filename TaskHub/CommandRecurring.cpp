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

bool isLeapYear (int year) {
	bool isLeapYear=false;
	if ((year%4==0)&&(year%100 !=0)||(year%400 ==0)) {
		isLeapYear=true;
	}

	return isLeapYear;
}

int getDayNumberInOneMonth (int Month, int year) {
	int solarMonth=31;
	int lunarMonth=30;
	int normalFeburaryDay=28;
	int leapFeburaryDay=29;
	if (Month==1||Month==3||Month==5||Month==7||Month==8||Month==10||Month==12) {
		return solarMonth;
	} else if (Month==4||Month==6||Month==9||Month==11) {
		return lunarMonth;
	} else if (isLeapYear(year)){
		return leapFeburaryDay;
	} else {
		return normalFeburaryDay;
	}
}

int countDays(int startingMonth, int startingDay, int endingMonth, int endingDay) {


	return 0;
}

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
	int year=2015;
	for (int j=startingMonth;j<=endingMonth;j++) {
		int dayNumber;
		if (j!=endingMonth) {
		dayNumber=getDayNumberInOneMonth(j,year);
		} else {
			dayNumber=endingDay;
		}

		for (int i=startingDay;i<=dayNumber;i++) {
			char taskname[256];
			strcpy_s(taskname, taskName.c_str());
			string message=taskname+EMPTY_SPACE+" -from "+startingTime+" -to "+endingTime+" "+to_string(i)+"/"+to_string(j);
			CommandAdd::addMessage(message);

		}
		startingDay=1;
	}
	return MESSAGE_RECURRING_TASK_SET;
}