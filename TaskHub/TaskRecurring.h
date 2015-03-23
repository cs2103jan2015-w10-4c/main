//@author A0111322E

/*
	Recurring tasks are tasks that occurs frequently at a fixed intervals. i.e. it could occur daily, weekly,
	monthly or annually etc.
*/

#pragma once

#include "TaskStorage.h"

class TaskRecurring : public TaskStorage{
public:
	TaskRecurring();
	~TaskRecurring();

protected:
	int _month;
	int _day;
	std::string _startTime;
	std::string _endTime;
};

