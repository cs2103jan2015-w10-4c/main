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
	static string showDayTask(string userMessage);
	static vector <string> messageDisplayed;
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