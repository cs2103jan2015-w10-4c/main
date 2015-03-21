//@author A0111322E

/*
	The TaskStorage class is the fundamental class that records the essential details of a task.
	It acts as a base class which will give other derived classes to classify the different tasks
	into floating tasks, deadline tasks and so on.
	The description of the different derived classes will be further elaborated in the respective 
	header files.
*/

#pragma once
#include <iostream>

class TaskStorage{

public:
	TaskStorage();
	~TaskStorage();

protected:
	std::string _taskTitle;
	bool isCompleted;

};

