//@author A0115793Y
//
//************************************************
//				Class CommandClash
//this class is to check whether the given time period
//on a given day or by default today clashes with existing tasks.
//
//************************************************
#ifndef CLASH_H_
#define CLASH_H_

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "LogicController.h"
#include "Parser.h"
#include "ShowDailyTask.h"

using namespace std;

class CommandClash
{
private:
	static bool isTwoClash(int startTime1, int endTime1,int startTime2, int endTime2);
public:
	static string clash(string input);
	static vector<Task> getDayTasks(vector<Task> allTask, int day, int month);
};

#endif
