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

int CommandRecurring::getDayNumberInOneMonth (int Month, int year) {
	int solarMonth = 31;
	int lunarMonth = 30;
	int normalFeburaryDay = 28;
	int leapFeburaryDay = 29;

	if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) {
		return solarMonth;
	} else if (Month == 4 || Month == 6 || Month == 9 || Month == 11) {
		return lunarMonth;
	} else if (isLeapYear(year)) {
		return leapFeburaryDay;
	} else {
		return normalFeburaryDay;
	}
}

void CommandRecurring::checkWithinRange (int &startingDay, int &startingMonth,int &year) {
	if (startingMonth == 1 || startingMonth == 3 || startingMonth == 5 || startingMonth == 7 || startingMonth == 8 || startingMonth == 10) {
		if (startingDay > 31) {
			startingDay -= 31;
			startingMonth += 1;
		}
	} else if (startingMonth == 12)  {
		if (startingDay > 31) {
			startingDay -= 31;
			startingMonth = 1;
			year++;
		}
	}
	else if (startingMonth == 4 || startingMonth == 6 || startingMonth == 9 || startingMonth == 11)  {
		if (startingDay > 30) {
			startingDay -= 30;
			startingMonth += 1;
		}
	} else if (isLeapYear(year)){
		if (startingDay > 29) {
			startingDay -= 29;
			startingMonth += 1;
		}
	} else if (!isLeapYear(year)) {
		if (startingDay > 28) {
			startingDay -= 28;
			startingMonth += 1;
		}
	}

	return;
}


bool CommandRecurring::isValidDay (int day, int month, int year) {
	bool isValid = false;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
		if(day <= 31) {
			isValid = true;
		}
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day <= 30) {
			isValid = true;
		}
	} else if (isLeapYear(year)){
		if (day <= 29) {
			isValid = true;
		}
	} else if (!isLeapYear(year)){
		if (day <= 28) {
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
	startingDate=input.substr(get_Start_Date - 2, 5);
	} 

	string startingTime;
	if (get_Start_Time != string::npos) {
		startingTime = input.substr(get_Start_Time - 2, 5);
	}
	
	string endingTime;
	if (get_End_Time != string::npos) {
		endingTime = input.substr(get_End_Time - 2, 5);
	}

	int endingHour;
	int endingMinute;
	if (get_End_Time != string::npos) {
	endingHour = atoi(input.substr(get_End_Time - 2, 2).c_str());
	endingMinute = atoi(input.substr(get_End_Time + 1, 2).c_str());
	} else {
		endingHour = 23;
		endingMinute = 59;
	}

	int endingDay;
	int endingMonth;
	if (get_End_Date != string::npos) {
	endingDay = atoi(input.substr(get_End_Date - 2, 2).c_str());
	endingMonth = atoi(input.substr(get_End_Date + 1, 2).c_str());
	} else {
		endingDay = currentTimeData._day;
		endingMonth = currentTimeData._mon;
	}
	
	int startingYear;
	int endingYear;
	if(get_year != string::npos) {
		if ((input.substr(get_year - 1, 1) != " ")) {
			startingYear = atoi(input.substr(get_year - 4, 4).c_str());
		} else {
			startingYear = currentTimeData._year;
		}
			endingYear = atoi(input.substr(get_year + 1, 4).c_str());
	} else {
			startingYear = currentTimeData._year;
			endingYear = currentTimeData._year;
	}

	int startingDay;
	int startingMonth;
	if ((get_Start_Date != string::npos)&&(get_Start_Date != get_End_Date)) {
	startingDay = atoi(input.substr(get_Start_Date - 2, 2).c_str());
	startingMonth = atoi(input.substr(get_Start_Date + 1, 2).c_str());
	} else {
		startingDay = currentTimeData._day;
		startingMonth = currentTimeData._mon;
	}

	

	int startingHour;
	int startingMinute;
	if ((get_Start_Time != string::npos)&&(get_Start_Time != get_End_Time)) {
	startingHour = atoi(input.substr(get_Start_Time - 2, 2).c_str());
	startingMinute = atoi(input.substr(get_Start_Time + 1, 2).c_str());;
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
					startingDay += 7;//get next date with the same day of week
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
					currentTimeData._dayOfWeek=(currentTimeData._dayOfWeek+dayAdvanced)%7;
			
					if (currentTimeData._dayOfWeek == 0) {
						currentTimeData._dayOfWeek = tempDayOfWeek;
					}
					startingDay = startingDay + abs(currentTimeData._dayOfWeek-weekday);
					} else if ((startingMonth == currentTimeData._mon)&&(startingDay != currentTimeData._day)) {
		
						dayAdvanced=startingDay - currentTimeData._day;
						int tempDayOfWeek = currentTimeData._dayOfWeek;
						currentTimeData._dayOfWeek += dayAdvanced;
						currentTimeData._dayOfWeek = currentTimeData._dayOfWeek % 7;
						if (currentTimeData._dayOfWeek == 0) {
							currentTimeData._dayOfWeek = 7;
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
			monthNumber = 12;
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
		startingMonth = 1;
	}
	return MESSAGE_RECURRING_TASK_SET;
	} //monthly
	else if (dayOfWeek.size() ==  MONTHLY){
		int recurringDay = atoi(dayOfWeek.substr(7,2).c_str());
		for (int k = startingYear; k <= endingYear; k++) {
		int monthNumber;
		if (k != endingYear) {
			monthNumber = 12;
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
		startingMonth = 1;
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
			monthNumber = 12;
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
		startingMonth = 1;
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
			monthNumber = 12;
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
			startingDay = 1;
		}
		startingMonth = 1;
	}
		StorageController::updateSaveFile();
		return MESSAGE_RECURRING_TASK_SET;
	 } else {
		 return MESSAGE_WRONG;
	}
	}
	
}

