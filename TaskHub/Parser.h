#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include "DateParser.h"
#include "TimeParser.h"
#include "VenueParser.h"
using namespace std;

class Task
{
private:
	string _TaskName;
	string _TaskType;
	string _startTime;
	string _endTime;
	string _deadlineTime;
	string _scheduledDate;
	string _deadlineDate;
	string _status;
	string _venue;
	int _integerDay;
	int _integerMonth;
<<<<<<< HEAD
	int _startHour;
	int _startMinute;
	int _endHour;
	int _endMinute;
=======
	int _hour;
	int _minute;
>>>>>>> 406445856a424c95f96b866652307badb6ccb5b3
	enum UPDATE_COMMAND
	{
		VENUE,TIME,DATE,TASK,INVALID
	};

public:
	//vector<string> Task;
	Task();
	Task(string input);
	~Task();
	Task(string Task, string input);
	string ToString();
	string getTaskName();
	string getTaskType();
	string getStartTime();
	string getEndTime();
	string getDeadlineTime();
	string getScheduledDate();
	string getDeadlineDate();
	string getStatus();
	string getVenue();
	int getIntegerDay();
	int getIntegerMonth();
<<<<<<< HEAD
	int getStartHour();
	int getStartMinute();
	int getEndHour();
	int getEndMinute();
=======
	int getHour();
	int getMinute();
>>>>>>> 406445856a424c95f96b866652307badb6ccb5b3
	void UpdateTask(string input);
	void MarkDone();
	void MarkUndone();
	void checkInputValidation();
	void markUncompleted();
	UPDATE_COMMAND determineUpdateCommandType(string updateCommand);
};

#endif