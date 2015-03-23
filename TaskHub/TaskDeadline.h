//@author A0111322E

/*
	Deadline tasks, as the name suggested, indicates that this particular type of tasks will have a deadline
	which can be a particular day along with the time.
*/

#pragma once

#include "TaskStorage.h"

class TaskDeadline : public TaskStorage{

public:
	TaskDeadline();
	~TaskDeadline();

protected:
	int _month;
	int _day;
	std::string _startTime;
	std::string _endTime;
};

