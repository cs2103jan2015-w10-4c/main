#ifndef CLASH_H_
#define CLASH_H_

#include <iostream>
#include <string>
#include <vector>
#include "Logic.h"
#include "Parser.h"
#include <windows.h>
#include <algorithm>
#include "ShowDailyTask.h"

using namespace std;

class CommandClash
{
private:
	bool isTwoClash(int startTime1, int endTime1,int startTime2, int endTime2);
public:
	string Clash(string input);
	vector<Task> getDayTask(vector<Task> allTask, int day, int month);
};
#endif
