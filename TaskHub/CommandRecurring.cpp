#include <sstream>
#include <fstream>
#include <string>
#include <Windows.h>
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
const string MONDAY="1";
const string TUESDAY="2";
const string WEDNESDAY="3";
const string THURSDAY="4";
const string FRIDAY="5";
const string SATURDAY="6";
const string SUNDAY="7";

string determineDayOfWeek (string input) {
	string dayOfWeek;
	dayOfWeek=input.substr(7,3);
	transform(dayOfWeek.begin(),dayOfWeek.end(),dayOfWeek.begin(), ::tolower);
	
	if (dayOfWeek=="mon") {
		return MONDAY;
	} else if (dayOfWeek=="tue") {
		return TUESDAY;
	} else if (dayOfWeek=="wed") {
		return WEDNESDAY;
	} else if (dayOfWeek=="thu") {
		return THURSDAY;
	} else if(dayOfWeek=="fri") {
		return FRIDAY;
	} else if (dayOfWeek=="sat") {
		return SATURDAY;
	} else if (dayOfWeek=="sun") {
		return SUNDAY;
	} else {
		return"invalid";
	}
}

void getTime(Time &time) {

	SYSTEMTIME lt;
    GetLocalTime(&lt);
  
	time._day=lt.wDay;
	time._mon=lt.wMonth;
	time._hour=lt.wHour;
	time._min=lt.wMinute;
	time._dayOfWeek=lt.wDayOfWeek;
	time._year=lt.wYear;

}


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

void checkWithinRange (int &startingDay, int &startingMonth,int &year) {
	if (startingMonth==1||startingMonth==3||startingMonth==5||startingMonth==7||startingMonth==8||startingMonth==10) {
		if (startingDay>31) {
			startingDay-=31;
			startingMonth+=1;
		}
	} else if (startingMonth==12)  {
		if (startingDay>31) {
			startingDay-=31;
			startingMonth=1;
			year++;
		}
	}
	else if (startingMonth==4||startingMonth==6||startingMonth==9||startingMonth==11)  {
		if (startingDay>30) {
			startingDay-=30;
			startingMonth+=1;
		}
	} else if (isLeapYear(year)){
		if (startingDay>29) {
			startingDay-=29;
			startingMonth+=1;
		}
	} else if (!isLeapYear(year)) {
		if (startingDay>28) {
			startingDay-=28;
			startingMonth+=1;
		}
	}

	return;
}

string CommandRecurring::setRecurringTask(string input) {

	Time currentTimeData;
	getTime(currentTimeData);

	size_t get_Start_Time;
	size_t get_Start_Date;
	size_t get_End_Time;
	size_t get_End_Date;
	size_t get_Venue;
	size_t get_TaskName;
	size_t get_year;
	size_t get_day_of_week;
	
	get_year=input.find_last_of("~");
	get_Start_Date=input.find("/");
	get_End_Date=input.find_last_of("/");
	get_Start_Time=input.find_first_of(":");
	get_End_Time=input.find_last_of(":");
	get_Venue=input.find("@");
	get_TaskName=input.find_first_of("/")-3;
	get_day_of_week=input.find("-every");

	string taskName=input.substr(0,get_TaskName);
	string startingDate=input.substr(get_Start_Date-2,5);
	string startingTime=input.substr(get_Start_Time-2,5);
	string endingTime=input.substr(get_End_Time-2,5);
	
	int weekday;
	

	string dayOfWeek=determineDayOfWeek(input.substr(get_day_of_week));

	if( dayOfWeek!="invalid") {
		weekday=atoi(dayOfWeek.c_str());
	} else {
		weekday=currentTimeData._dayOfWeek;
	}

	int startingYear;
	int endingYear;
	if(get_year!=string::npos) {
		if ((input.substr(get_year-1,1)!=" ")) {
			startingYear=atoi(input.substr(get_year-4,4).c_str());
		} else {
			startingYear=currentTimeData._year;
		}
			endingYear=atoi(input.substr(get_year+1,4).c_str());
	} else {
			startingYear=currentTimeData._year;
			endingYear=currentTimeData._year;
	}

	int startingDay;
	int startingMonth;
	if ((get_Start_Date!=string::npos)&&(get_Start_Date!=get_End_Date)) {
	startingDay=atoi(input.substr(get_Start_Date-2,2).c_str());
	startingMonth=atoi(input.substr(get_Start_Date+1,2).c_str());
	} else {
		startingDay=currentTimeData._day;
		startingMonth=currentTimeData._mon;
	}

	int startingHour;
	int startingMinute;
	if ((get_Start_Time!=string::npos)&&(get_Start_Time!=get_End_Time)) {
	startingHour=atoi(input.substr(get_Start_Time-2,2).c_str());
	startingMinute=atoi(input.substr(get_Start_Time+1,2).c_str());;
	} else {
		startingHour=currentTimeData._hour;
		startingMinute=currentTimeData._min;
	}


	int endingDay=atoi(input.substr(get_End_Date-2,2).c_str());
	int endingMonth=atoi(input.substr(get_End_Date+1,2).c_str());
	int endingHour=atoi(input.substr(get_End_Time-2,2).c_str());
	int endingMinute=atoi(input.substr(get_End_Time+1,2).c_str());;
	
	
	string venue="";
	
	startingDay=startingDay+weekday-currentTimeData._dayOfWeek;
	checkWithinRange(startingDay,startingMonth,startingYear);

	int interval;
	if (get_day_of_week!=string::npos) {
		interval=7;
	} else {
		interval=1;
	}

	for (int k=startingYear; k<=endingYear; k++) {
		int monthNumber;
		if (k!=endingYear) {
			monthNumber=12;
		} else {
			monthNumber=endingMonth;
		}
		for (int j=startingMonth;j<=monthNumber;j++) {
			int dayNumber;
			if (j!=endingMonth) {
			dayNumber=getDayNumberInOneMonth(j,k);
			} else {
				dayNumber=endingDay;
			}

			for (int i=startingDay;i<=dayNumber;i=i+interval) {
				char taskname[256];
				strcpy_s(taskname, taskName.c_str());
				string message=taskname+EMPTY_SPACE+" -from "+startingTime+" -to "+endingTime+" "+to_string(i)+"/"+to_string(j);
				CommandAdd::addMessage(message);
	
			}
			startingDay=1;
		}
		startingMonth=1;
	}
	return MESSAGE_RECURRING_TASK_SET;
}


	/*
	string startingDayString=input.substr(get_Start_Date-2,2);
	string startingMonthString=input.substr(get_Start_Date+1,2);
	string endingDayString=input.substr(get_End_Date-2,2);
	string endingMonthString=input.substr(get_End_Date+1,2);
	string startingHourString=input.substr(get_Start_Time-2,2);
	string startingMinuteString=input.substr(get_Start_Time+1,2);
	string endingHourString=input.substr(get_End_Time-2,2);
	string endingMinutStringe=input.substr(get_End_Time+1,2);*/

