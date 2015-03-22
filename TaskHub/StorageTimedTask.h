//@author A0111322E

/*
	Timed tasks could either:
	a)	occur for the entire day, or
	b)	occur for a specific time period within a day, or
	c)	occur from day to day.
*/

#pragma once

#include "TaskStorage.h"

class StorageTimedTask : public TaskStorage{

public:
	StorageTimedTask();
	~StorageTimedTask();

protected:
	int _month;
	int _day;
	std::string _startTime;
	std::string _endTime;
};

