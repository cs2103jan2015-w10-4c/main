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
	void UpdateTask(string input);
	void MarkDone();
	void MarkUndone();
	void checkInputValidation();
	void markUncompleted();
	
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
};

#endif