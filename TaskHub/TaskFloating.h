//@author A0111322E

/*
	Floating tasks have no start time nor end time, and there is also no specific deadline.
*/

#pragma once

#include "TaskStorage.h"

class TaskFloating : public TaskStorage{

public:
	TaskFloating();
	~TaskFloating();

protected:

};

