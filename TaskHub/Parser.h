#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <string>
#include "DateParser.h"
#include "TimeParser.h"
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
	string get_TaskName();
	void UpdateTask(string input);
	void MarkDone();
	void MarkUndone();
	void checkInputValidation();
	
private:
	string _TaskName;
	string _TaskType;
	string _startTime;
	string _endTime;
	string _deadlineTime;
	string _scheduledDate;
	string _deadlineDate;
	string _status;
	DateParser _dateParser;
	TimeParser _timeParser;

};

#endif