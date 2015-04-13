//@author A0115365J

//
//************************************************
//				Class ShowDailyTask
//this class is used when the show command is called
//it can show tasks on today, tomorrow, or now
//it can also show tasks on any other date with dd/mm format
//by default it shows today
//
//
//it can also show free slots of any other date, with format dd/mm
//************************************************

#ifndef SHOWDAILYTASK_H_
#define SHOWDAILYTASK_H_

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct localTime{
		int _day;
		int _mon;
		int _hour;
		int _min;
	};

class ShowDailyTask {
public:
	ShowDailyTask ();
	~ShowDailyTask ();
	
	static vector <string> messageDisplayed;

	static string showDayTask(string userMessage);
	static vector <string> ShowTask (vector <int> taskIndex);
	static vector <string> checkFreeSlot (vector <int> taskIndex);

	static void getDayTask (vector <Task> & temporary, vector <int> &taskIndex, int currentMonth, int currentDay);
	static void getHourTask (vector <Task> &temporary, vector <int> &taskIndex, int currentMonth, int currentDay, int currentHour);
private:
	static void getSystemTime(localTime &time);
	
	static const string MESSAGE_TODAY;
	static const string MESSAGE_SHOW;
	static const string MESSAGE_TOMORROW;
	static const string MESSAGE_SECOND_COMMAND;
	static const string MESSAGE_NOW;
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_FREE_SLOT_SHOWN;
	static const string MESSAGE_TASK_SHOWN;
};

#endif