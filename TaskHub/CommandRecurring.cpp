#include <sstream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Logic.h"
#include "CommandAdd.h"
#include "CommandRecurring.h"

const int CommandRecurring::DAYSIZE = 14;
const int CommandRecurring::DAYOFWEEKSIZE = 10;
const int CommandRecurring::DEFAULT = 7;
const int CommandRecurring::MONTHLY = 9;
const int CommandRecurring::MAX_BUFFERING_CAPACITY = 256;

const int CommandRecurring::NOOFDAYSPERWEEK = 7;
const int CommandRecurring::YEARWIDTH = 4;
const int CommandRecurring::TIMEWIDTH = 5;
const int CommandRecurring::DATEWIDTH= 5;
const int CommandRecurring::HRORMINWIDTH = 2;
const int CommandRecurring::MONORDAYWIDTH = 2;
const int CommandRecurring::CORRECTPLACE = 1;
const int CommandRecurring::intSUNDAY = 7;
const int CommandRecurring::intJan = 1;
const int CommandRecurring::FIRSTDAYINAMONTH = 1;
const int CommandRecurring::MONTHNOPERYEAR = 12;

const int CommandRecurring::JAN = 1;
const int CommandRecurring::FEB= 2;
const int CommandRecurring::MAR = 3;
const int CommandRecurring::APR= 4;
const int CommandRecurring::MAY = 5;
const int CommandRecurring::JUN = 6;
const int CommandRecurring::JULY = 7;
const int CommandRecurring::AUG = 8;
const int CommandRecurring::SEP = 9;
const int CommandRecurring::OCT = 10;
const int CommandRecurring::NOV = 11;
const int CommandRecurring::DEC = 12;
const int CommandRecurring::SOLARMONTH = 31;
const int CommandRecurring::LUNARMONTH = 30;
const int CommandRecurring::FEBURARYDAY = 28;
const int CommandRecurring::LEAPFEBURARYDAY = 29;

const string CommandRecurring::COMMAND_TYPE="recurring";
const string CommandRecurring::MESSAGE_RECURRING_TASK_SET="Recurring tasks have been set";
const string CommandRecurring::MESSAGE_WRONG="Wrong message";
const string CommandRecurring::MESSAGE_INVALID="invalid";
const string CommandRecurring::MESSAGE_DEFAULT="default";
const string CommandRecurring::EMPTY_SPACE=" ";
const string CommandRecurring::MONDAY="1";
const string CommandRecurring::TUESDAY="2";		
const string CommandRecurring::WEDNESDAY="3";
const string CommandRecurring::THURSDAY="4";
const string CommandRecurring::FRIDAY="5";
const string CommandRecurring::SATURDAY="6";
const string CommandRecurring::SUNDAY="7";


CommandRecurring::CommandRecurring (string input) {
	
}

CommandRecurring::~CommandRecurring () {
	
}

string CommandRecurring::determineDayOfWeek (string input) {
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

void CommandRecurring::getTime (Time &time) {

	SYSTEMTIME lt;
    GetLocalTime(&lt);
  
	time._day = lt.wDay;
	time._mon = lt.wMonth;
	time._hour = lt.wHour;
	time._min = lt.wMinute;
	time._dayOfWeek = lt.wDayOfWeek;
	time._year = lt.wYear;

}


bool CommandRecurring::isLeapYear (int year) {
	bool isLeapYear = false;
	if ((year % 4 == 0)&&(year % 100 != 0)||(year % 400 == 0)) {
		isLeapYear = true;
	}

	return isLeapYear;
}

int CommandRecurring::getDayNumberInOneMonth (int month, int year) {

	if (month == JAN || month == MAR || month == MAY || month == JULY || month == AUG || month == OCT || month == DEC) {
		return SOLARMONTH;
	} else if (month == APR || month == JUN || month == SEP || month == NOV) {
		return LUNARMONTH;
	} else if (isLeapYear(year)) {
		return LEAPFEBURARYDAY;
	} else {
		return FEBURARYDAY;
	}
}

void CommandRecurring::checkWithinRange (int &startingDay, int &startingMonth,int &year) {
	if (startingMonth == JAN || startingMonth == MAR || startingMonth == MAY || startingMonth == JULY || startingMonth == AUG || startingMonth == OCT) {
		if (startingDay > SOLARMONTH) {
			startingDay -= SOLARMONTH;
			startingMonth += 1;
		}
	} else if (startingMonth == DEC)  {
		if (startingDay > SOLARMONTH) {
			startingDay -= SOLARMONTH;
			startingMonth = 1;
			year++;
		}
	}
	else if (startingMonth == APR || startingMonth == JUN || startingMonth == SEP || startingMonth == NOV)  {
		if (startingDay > LUNARMONTH) {
			startingDay -= LUNARMONTH;
			startingMonth += 1;
		}
	} else if (isLeapYear(year)){
		if (startingDay > LEAPFEBURARYDAY) {
			startingDay -= LEAPFEBURARYDAY;
			startingMonth += 1;
		}
	} else if (!isLeapYear(year)) {
		if (startingDay > FEBURARYDAY) {
			startingDay -= FEBURARYDAY;
			startingMonth += 1;
		}
	}

	return;
}


bool CommandRecurring::isValidDay (int day, int month, int year) {
	bool isValid = false;
	if (month == JAN || month == MAR || month == MAY || month == JULY || month == AUG || month == OCT || month == DEC) {
		if(day <= SOLARMONTH) {
			isValid = true;
		}
	} else if (month == APR || month == JUN || month == SEP || month == NOV) {
		if (day <= LUNARMONTH) {
			isValid = true;
		}
	} else if (isLeapYear(year)){
		if (day <= LEAPFEBURARYDAY) {
			isValid = true;
		}
	} else if (!isLeapYear(year)){
		if (day <= FEBURARYDAY) {
			isValid = true;
		}
	}
	return isValid;
}

string RecurDay () {

	return "";
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
	
	get_year = input.find_last_of("~");
	get_Start_Date = input.find("/");
	get_End_Date = input.find_last_of("/");
	get_Start_Time = input.find_first_of(":");
	get_End_Time = input.find_last_of(":");
	get_Venue = input.find("@");
	get_day_of_week = input.find("-every");
	get_TaskName = input.find_first_of("/");

	string taskName;
	if (get_TaskName != string::npos) {
		string temp = input.substr(0,get_TaskName);
		taskName = input.substr(0,temp.find_last_of(" "));
	} else {
		taskName = input;
	}
	
	string startingDate;
	if (get_Start_Date != string::npos) {
		startingDate=input.substr(get_Start_Date - MONORDAYWIDTH, DATEWIDTH);
	} 

	string startingTime;
	if (get_Start_Time != string::npos) {
		startingTime = input.substr(get_Start_Time - HRORMINWIDTH, TIMEWIDTH);
	}
	
	string endingTime;
	if (get_End_Time != string::npos) {
		endingTime = input.substr(get_End_Time - HRORMINWIDTH, TIMEWIDTH);
	}

	int endingHour;
	int endingMinute;
	if (get_End_Time != string::npos) {
		endingHour = atoi(input.substr(get_End_Time - HRORMINWIDTH, HRORMINWIDTH).c_str());
		endingMinute = atoi(input.substr(get_End_Time + CORRECTPLACE, HRORMINWIDTH).c_str());
	} else {
		endingHour = 23;
		endingMinute = 59;
	}

	int endingDay;
	int endingMonth;
	if (get_End_Date != string::npos) {
		endingDay = atoi(input.substr(get_End_Date - MONORDAYWIDTH, MONORDAYWIDTH).c_str());
		endingMonth = atoi(input.substr(get_End_Date + CORRECTPLACE, MONORDAYWIDTH).c_str());
	} else {
		endingDay = currentTimeData._day;
		endingMonth = currentTimeData._mon;
	}
	
	int startingYear;
	int endingYear;
	if(get_year != string::npos) {
		if ((input.substr(get_year - CORRECTPLACE, CORRECTPLACE) != " ")) {
			startingYear = atoi(input.substr(get_year - YEARWIDTH, YEARWIDTH).c_str());
		} else {
			startingYear = currentTimeData._year;
		}
		endingYear = atoi(input.substr(get_year + CORRECTPLACE, YEARWIDTH).c_str());
	} else {
			startingYear = currentTimeData._year;
			endingYear = currentTimeData._year;
	}

	int startingDay;
	int startingMonth;
	if ((get_Start_Date != string::npos)&&(get_Start_Date != get_End_Date)) {
		startingDay = atoi(input.substr(get_Start_Date - MONORDAYWIDTH, MONORDAYWIDTH).c_str());
		startingMonth = atoi(input.substr(get_Start_Date + CORRECTPLACE, MONORDAYWIDTH).c_str());
	} else {
		startingDay = currentTimeData._day;
		startingMonth = currentTimeData._mon;
	}

	

	int startingHour;
	int startingMinute;
	if ((get_Start_Time != string::npos)&&(get_Start_Time != get_End_Time)) {
		startingHour = atoi(input.substr(get_Start_Time - HRORMINWIDTH, HRORMINWIDTH).c_str());
		startingMinute = atoi(input.substr(get_Start_Time + CORRECTPLACE, HRORMINWIDTH).c_str());;
	} else {
		startingHour = currentTimeData._hour;
		startingMinute = currentTimeData._min;
		startingTime = to_string(startingHour) + ":" + to_string(startingMinute);
	}

	
	
	string venue = "";
	
	string dayOfWeek;
	if (get_day_of_week != string::npos) {
		dayOfWeek = input.substr(get_day_of_week);
	}
	else {
		dayOfWeek = MESSAGE_DEFAULT;
	}

	int interval;
	if (get_day_of_week != string::npos) {
		interval = 7;
	} else {
		interval = 1;
	}
	
	int weekday;
	if (get_day_of_week != string::npos) {
	
		if (dayOfWeek.size() == DAYOFWEEKSIZE){
			dayOfWeek = determineDayOfWeek(input.substr(get_day_of_week));
			if( dayOfWeek != MESSAGE_INVALID) {
			weekday = atoi(dayOfWeek.c_str());
			} else {
				weekday = currentTimeData._dayOfWeek;
			}

			if (startingDay == currentTimeData._day&&startingMonth == currentTimeData._mon) {
				startingDay = startingDay + weekday - currentTimeData._dayOfWeek;// get last date with the same day of week

				if (weekday < currentTimeData._dayOfWeek) {
					startingDay += DEFAULT;//get next date with the same day of week
				}
				checkWithinRange(startingDay,startingMonth,startingYear);
			} else {
				//set to correct day of the week for the starting day, week task only up to this year
				int dayAdvanced = 0;
				if ((startingMonth != currentTimeData._mon)/*&&(startingDay!=currentTimeData._day)*/) {
					int tempMonth = currentTimeData._mon;
					while (tempMonth < startingMonth) {
						dayAdvanced += getDayNumberInOneMonth(tempMonth,currentTimeData._year);
						tempMonth++;
					}
					dayAdvanced = dayAdvanced + startingDay - currentTimeData._day;
			
					int tempDayOfWeek = currentTimeData._dayOfWeek;
					currentTimeData._dayOfWeek=(currentTimeData._dayOfWeek+dayAdvanced) % NOOFDAYSPERWEEK;
			
					if (currentTimeData._dayOfWeek == 0) {
						currentTimeData._dayOfWeek = tempDayOfWeek;
					}
					startingDay = startingDay + abs(currentTimeData._dayOfWeek-weekday);
					} else if ((startingMonth == currentTimeData._mon)&&(startingDay != currentTimeData._day)) {
		
						dayAdvanced=startingDay - currentTimeData._day;
						int tempDayOfWeek = currentTimeData._dayOfWeek;
						currentTimeData._dayOfWeek += dayAdvanced;
						currentTimeData._dayOfWeek = currentTimeData._dayOfWeek % NOOFDAYSPERWEEK;
						if (currentTimeData._dayOfWeek == 0) {
							currentTimeData._dayOfWeek = intSUNDAY;
						}
						startingDay = startingDay+weekday - currentTimeData._dayOfWeek;// get last date with the same day of week
						startingDay += 7;//get next date with the same day of week this one correct
					}
			}
	//recur weekly and daily
	int i;
	int j;
	int k;
	for ( k = startingYear; k <= endingYear; k++) {
		int monthNumber;
		if (k != endingYear) {
			monthNumber = MONTHNOPERYEAR;
		} else {
			monthNumber = endingMonth;
		}
		for ( j = startingMonth;j <= monthNumber;j++) {
			int dayNumber;
			if (j != endingMonth) {
			dayNumber = getDayNumberInOneMonth(j,k);
			} else {
				dayNumber = endingDay;
			}
			
			for (i = startingDay; i <= dayNumber; i = i + interval) {
				char taskname[MAX_BUFFERING_CAPACITY];
				strcpy_s(taskname, taskName.c_str());
				if (get_End_Time != string::npos) {
				string message = taskname+EMPTY_SPACE + " -from " + startingTime + " -to " + endingTime + " " + to_string(i) + "/" + to_string(j);
				CommandAdd::addMessage(message);
				} else {
				string message = taskname;
				CommandAdd::addMessage(message);
				}
	
			}
			startingDay = i-dayNumber;
		}
		startingMonth = intJan;
	}
	return MESSAGE_RECURRING_TASK_SET;
	} //monthly
	else if (dayOfWeek.size() ==  MONTHLY){
		int recurringDay = atoi(dayOfWeek.substr(7,2).c_str());
		for (int k = startingYear; k <= endingYear; k++) {
		int monthNumber;
		if (k != endingYear) {
			monthNumber = MONTHNOPERYEAR;
		} else {
			monthNumber = endingMonth;
		}
		for (int j = startingMonth; j <= monthNumber; j++) {
			
			startingDay = recurringDay;
			if (isValidDay(startingDay,j,k)) {
			//for (int i=startingDay;i<=dayNumber;i=i+interval) {
				char taskname[MAX_BUFFERING_CAPACITY];
				strcpy_s(taskname, taskName.c_str());
				if (get_End_Time != string::npos) {
					string message = taskname + EMPTY_SPACE + " -from " + startingTime + " -to " + endingTime + to_string(startingDay) + "/" + to_string(j);
				CommandAdd::addMessage(message);
				} else {
				string message = taskname;
				CommandAdd::addMessage(message);
				}
			}
			
		}
		startingMonth = intJan;
	}
		return MESSAGE_RECURRING_TASK_SET;
	}//any days as interval
	else if (dayOfWeek.size() == DAYSIZE){
		int i;
		int j;
		int k;
		int interval; 
		interval = atoi(dayOfWeek.substr(7,2).c_str());

		for ( k = startingYear; k <= endingYear; k++) {
		int monthNumber;
		if (k != endingYear) {
			monthNumber = MONTHNOPERYEAR;
		} else {
			monthNumber = endingMonth;
		}
		for ( j = startingMonth;j <= monthNumber; j++) {
			int dayNumber;
			if (j != endingMonth) {
			dayNumber = getDayNumberInOneMonth(j,k);
			} else {
				dayNumber = endingDay;
			}

			//checkWithinRange(startingDay,startingMonth,startingYear);
			for ( i = startingDay; i <= dayNumber;i = i + interval) {
				char taskname[MAX_BUFFERING_CAPACITY];
				strcpy_s(taskname, taskName.c_str());
				if (get_End_Time != string::npos) {
				string message = taskname + EMPTY_SPACE + " -from " + startingTime + " -to " + endingTime + " " + to_string(i) + "/" + to_string(j);
				CommandAdd::addMessage(message);
				} else {
				string message = taskname;
				CommandAdd::addMessage(message);
				}
	
			}
			startingDay = i - dayNumber;
		}
		startingMonth = intJan;
	}
		return MESSAGE_RECURRING_TASK_SET;
	 } else {
		 return MESSAGE_WRONG;
	}
	}
	// by default every day
	else {
		if (dayOfWeek.size() == DEFAULT){
		int i;
		int j;
		int k;
		int interval; 
		interval = atoi(dayOfWeek.substr(7,2).c_str());
		for ( k = startingYear; k <= endingYear; k++) {
		int monthNumber;
		if (k != endingYear) {
			monthNumber = MONTHNOPERYEAR;
		} else {
			monthNumber = endingMonth;
		}
		for ( j = startingMonth;j <= monthNumber; j++) {
			int dayNumber;
			if (j != endingMonth) {
			dayNumber = getDayNumberInOneMonth(j,k);
			} else {
				dayNumber = endingDay;
			}

			//checkWithinRange(startingDay,startingMonth,startingYear);
			for ( i = startingDay; i <= dayNumber; i++) {
				char taskname[MAX_BUFFERING_CAPACITY];
				strcpy_s(taskname, taskName.c_str());
				if (get_End_Time != string::npos) {
				string message = taskname + EMPTY_SPACE + " -from " + startingTime + " -to " + endingTime + " " + to_string(i) + "/" + to_string(j);
				CommandAdd::addMessage(message);
				} else {
				string message = taskname;
				CommandAdd::addMessage(message);
				}
	
			}
			startingDay = FIRSTDAYINAMONTH;
		}
		startingMonth = intJan;
	}
		StorageController::updateSaveFile();
		return MESSAGE_RECURRING_TASK_SET;
	 } else {
		 return MESSAGE_WRONG;
	}
	}
	
}

