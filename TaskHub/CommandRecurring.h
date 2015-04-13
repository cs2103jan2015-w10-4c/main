//@author A0115365J

//
//************************************************
//				Class CommandRecurring
//this class is used when the recurring command is called
//the following task type can be recurred: timed and deadline tasks
//
//the interval of recurring can be monthly, weekly, daily, or any days as interval, by default recurring interval is everyday
//
//when no time or date or year is keyed in, by default it is current time, date and year
//
//************************************************

#ifndef COMMANDRECURRING_H_
#define COMMANDRECURRING_H_

#include<iostream>
#include<string>
using namespace std;

struct Time {
	int _day;
	int _mon;
	int _hour;
	int _min;
	int _year;
	int _dayOfWeek;
};

class CommandRecurring {

public:
	CommandRecurring (string input);
	~CommandRecurring ();

	static int getDayNumberInOneMonth (int Month, int year);
	
	static bool isLeapYear (int year);
	static bool isValidDay (int day, int month, int year);
	static string setRecurringTask (string input);
	static string determineDayOfWeek (string input);
	static void getTime (Time &time);
	static void checkWithinRange (int &startingDay, int &startingMonth,int &year);
	static void getParameters (string input);
	
	static void InterpretInput (string input, size_t &get_year, size_t &get_Start_Date, size_t &get_End_Date, size_t &get_Start_Time, size_t &get_End_Time,
									   size_t &get_Venue, size_t &get_day_of_week, size_t &get_TaskName, size_t &get_deadline, Time &currentTimeData,
									   int &startingYear, int &endingYear, int &startingMonth, int &endingMonth, int &startingDay, int &endingDay, int &interval,
									   int &startingHour, int &endingHour, int &startingMinute, int &endingMinute, string &startingDate,
										string &dayOfWeek,string &startingTime, string &endingTime, string &taskName, string &venue);

	static void recDayDefault ( int startingYear, int endingYear, int startingMonth, int endingMonth, int startingDay, int endingDay,
					string dayOfWeek,string startingTime, string endingTime, string taskName, string venue, size_t found, size_t get_deadline);

	static void recDayOrWeek ( int startingYear, int endingYear, int startingMonth, int endingMonth, int startingDay, int endingDay, int interval,
					string dayOfWeek,string startingTime, string endingTime, string taskName, string venue, size_t found, size_t get_deadline);

	static void recMonth ( int startingYear, int endingYear, int startingMonth, int endingMonth, int startingDay, int endingDay, int interval,
					string dayOfWeek,string startingTime, string endingTime, string taskName, string venue, size_t found, size_t get_deadline);

	static int setStartingDay (string input, string dayOfWeek, Time currentTimeData, int startingDay, int startingMonth,
									  size_t get_day_of_week, int startingYear);
private:
	static const string COMMAND_TYPE;
	static const string MESSAGE_RECURRING_TASK_SET;
	static const string MESSAGE_WRONG;
	static const string MESSAGE_INVALID;
	static const string MESSAGE_DEFAULT;
	static const string EMPTY_SPACE;
	static const string MONDAY;
	static const string TUESDAY;
	static const string WEDNESDAY;
	static const string THURSDAY;
	static const string FRIDAY;
	static const string SATURDAY;
	static const string SUNDAY;
	
	static const int DAYSIZE;
	static const int DAYOFWEEKSIZE;
	static const int DEFAULT;
	static const int MONTHLY;
	static const int MAX_BUFFERING_CAPACITY;

	static const int JAN;
	static const int FEB;
	static const int MAR;
	static const int APR;
	static const int MAY;
	static const int JUN;
	static const int JULY;
	static const int AUG;
	static const int SEP;
	static const int OCT;
	static const int NOV;
	static const int DEC;

	static const int SOLARMONTH;
	static const int LUNARMONTH;
	static const int FEBURARYDAY;
	static const int LEAPFEBURARYDAY;

	static const int TIMEWIDTH;
	static const int DATEWIDTH;
	static const int HRORMINWIDTH;
	static const int MONORDAYWIDTH;
	static const int CORRECTPLACE;
	static const int YEARWIDTH;
	static const int NOOFDAYSPERWEEK;
	static const int intSUNDAY;
	static const int MONTHNOPERYEAR;
	static const int intJan;
	static const int FIRSTDAYINAMONTH;
	static const int DEFAULTENDINGHOUR;
	static const int DEFAULTENDINGMINUTE;

};


#endif