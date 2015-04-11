//author: A0115399W

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include "DateParser.h"
#include "TimeParser.h"
#include "VenueParser.h"
using namespace std;

class Task{

private:
	string _TaskName;
	string _TaskType;
	string _startTime;
	string _endTime;
	string _deadlineTime;
	string _scheduledDate;
	string _scheduledDateReverse;
	string _deadlineDate;
	string _status;
	string _venue;
	//string _alphaMonth;
	int _integerDay;
	int _integerMonth;
	int _startHour;
	int _startMinute;
	int _endHour;
	int _endMinute;



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
	string getScheduledDateReverse();
	string getDeadlineDate();
	string getStatus();
	string getVenue();
	int getIntegerDay();
	int getIntegerMonth();
	int getStartHour();
	int getStartMinute();
	int getEndHour();
	int getEndMinute();
	void UpdateTask(string input);
	void MarkDone();
	void MarkUndone();
	void checkInputValidation();
	void markUncompleted();
	static bool isValid;
};

#endif