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
	static string showDayTask(string userMessage);
	static vector <string> messageDisplayed;
private:
	static void getSystemTime(localTime &time);

};

#endif