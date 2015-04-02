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
	static string setRecurringTask (string input);
private:
	static const string COMMAND_TYPE;
	static const string MESSAGE_RECURRING_TASK_SET;


};


#endif