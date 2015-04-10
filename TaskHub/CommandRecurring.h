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
	static void getTime (Time &time);
	static void checkWithinRange (int &startingDay, int &startingMonth,int &year);
	static void getParameters (string input);
	static bool isLeapYear (int year);
	static bool isValidDay (int day, int month, int year);
	static string setRecurringTask (string input);
	static string determineDayOfWeek (string input);
	
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


};


#endif