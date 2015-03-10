
#ifndef THTask_H
#define THTask_H

#include <string>
#include "THTaskDueSoon.h"
#include "THUtilities.h"

//THTask is used to encapsulate the details of a task.
//By encapsulating the task details, THTask is able to provide relevant information through the public methods

class THTask {
public:

	THTask();
	//field setters
	void setTaskName(string);
	void setStartingDate(string);
	void setStartingTime(string);
	void setEndingDate(string);
	void setEndingTime(string);
	void setStatus(bool);
	//to check if fields are empty
	bool haveTaskName();
	bool haveStartingDate();
	bool haveStartingTime();
	bool haveEndingDate();
	bool haveEndingTime();
	//field getters
	string getTaskName();
	string getStartingDate();
	string getStartingTime();
	string getEndingDate();
    string getEndingTime();
	bool        getStatus();
	bool        checkOverdue();
	bool        checkToday();
	THUtilities::TaskType getTaskType();
	
private:

	string _taskName;
	string _StartingDate;
	string _StartingTime;
	string _EndingDate;
	string _EndingTime;
	bool        _isDone;
	bool        _isOverdue;
	bool        _isToday;

	THUtilities::TaskType _taskType;
	THTaskDueSoon _taskTime;

	void refresh();
	void updateTaskType();
	void rearrangeDateTime();
	int  stringToInt(string);
};
#endif
