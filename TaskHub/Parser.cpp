#include "Parser.h"
#include "TimeParser.h"
#include "DateParser.h"

const int Task_LEN = 250;
const string SCHEDULED_Task_LABEL = "timed";
const string DEADLINE_Task_LABEL = "deadline";
const string FLOATING_Task_LABEL = "floating";
const string PROCESSING_Task_LABEL = "progressing";
const string FINISHED_Task_LABEL = "done";
const string INVALID_DATE_MSG = "invalid date, provide valid date";
const string INVALID_TIME_MSG = "invalid time, provide valid time";

Task::Task(){}

Task::Task(string input){
	
	if (!input.empty()){
		size_t timed_Task = input.find("-from");
		size_t deadlined_Task = input.find("-by");
		size_t venue_Task = input.find("@");

		if (timed_Task != string::npos){
			DateParser parseDate(input);
		    TimeParser parseTime(input);
		
			_TaskType = SCHEDULED_Task_LABEL;
			_TaskName = input.substr(0, timed_Task - 1);
			_startTime = parseTime.getStartTime();
			_endTime = parseTime.getEndTime();
			_deadlineTime = "";
			_scheduledDate = parseDate.getDate();
			_deadlineDate = "";
			
		}
		else if (deadlined_Task != string::npos){
			DateParser parseDate(input);
		    TimeParser parseTime(input);
			_TaskType = DEADLINE_Task_LABEL;
			_TaskName = input.substr(0, deadlined_Task - 1);
			_startTime = "";
			_endTime = "";
			_deadlineTime = input.substr(deadlined_Task + 4, 5);
			_scheduledDate = "";
			_deadlineDate = parseDate.getDate();
		}
		else{
			_TaskType = FLOATING_Task_LABEL;
			_TaskName = input;
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledDate = "";
			_deadlineDate = "";
			
		}
		_status = "progressing";
	}
	if (venue_Task != string::npos){
		VenueParser parseVenue(input);
		_venue = parseVenue.getVenue();
	}
	checkInputValidation();
}

Task::~Task(){}

Task::Task(string Task, string input){
	if (!Task.empty()){

		//store _status
		size_t find__status = Task.find("progressing");
		if (find__status != string::npos){
			_status = "progressing";
		}
		else{
			size_t find__status = Task.find("done");
			if (find__status != string::npos){
				_status = "done";
			}
			else{
				_status = " ";
			}
		}

		//classify Tasks into scheduled, deadlined or floating
		size_t find_date = Task.find("/");
		string temp_date;
		string temp;	//to store remaining part of the Task arguement to check whether there is a time included there
		if (find_date != string::npos){	//date found, Task is either scheduled or deadlined.
			//assume double digit date
				_TaskName = Task.substr(0, find_date - 2);
				temp_date = Task.substr(find_date - 2, 5);


			size_t find_time = Task.find(":"); 
			temp = Task.substr(find_time + 2);
			size_t find_ending_time = temp.find(":");	//check if there's an ending time ie. seperate deadlined Task and scheduled Task

			if ((find_time != string::npos) && (find_ending_time != string::npos)){
				_TaskType = SCHEDULED_Task_LABEL;
				_startTime = Task.substr(find_time - 2, 5);
				_endTime = temp.substr(find_ending_time - 2, 5);
				_deadlineTime = "";
				_scheduledDate = temp_date;
				_deadlineDate = "";
			}
			else if (find_time != string::npos){
				_TaskType = DEADLINE_Task_LABEL;
				_startTime = "";
				_endTime = "";
				_deadlineTime = Task.substr(find_time - 2, 5);
				_scheduledDate = "";
				_deadlineDate = temp_date;
			}

		}
		else{
			_TaskType = FLOATING_Task_LABEL;
			_TaskName = Task.substr(0, find__status - 1);
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledDate = "";
			_deadlineDate = "";
		}
	}
	checkInputValidation();
}

string Task::ToString(){
	char Task[Task_LEN];
	strcpy_s(Task, _TaskName.c_str());
	if (_TaskType == DEADLINE_Task_LABEL){
		strcat_s(Task, " ");
		strcat_s(Task, _deadlineDate.c_str());
		strcat_s(Task, " ");
		strcat_s(Task, _deadlineTime.c_str());
		strcat_s(Task, " ");
		strcat_s(Task, _status.c_str());
	}
	else if (_TaskType == SCHEDULED_Task_LABEL){
		strcat_s(Task, " ");
		strcat_s(Task, _scheduledDate.c_str());
		strcat_s(Task, " ");
		strcat_s(Task, _startTime.c_str());
		strcat_s(Task, " ");
		strcat_s(Task, _endTime.c_str());
		strcat_s(Task, " ");
		strcat_s(Task, _status.c_str());
	}
	else if (_TaskType == FLOATING_Task_LABEL){
		strcat_s(Task, " ");
		strcat_s(Task, _status.c_str());
	}
	return Task;
}

string Task::getTaskName(){
	return _TaskName;
}

void Task::UpdateTask(string input){
	if (!input.empty()){
		size_t timed_Task = input.find("-from");
		size_t deadlined_Task = input.find("-by");
		if (timed_Task != string::npos){
			size_t ending_time = input.find("-to");
			size_t get_date = input.find("/");
			_TaskType = SCHEDULED_Task_LABEL;
			_startTime = input.substr(timed_Task + 6, 5);
			_endTime = input.substr(ending_time + 4, 5);
			if (get_date != string::npos){
				_scheduledDate = input.substr(get_date - 2, 5);
			}
		}
		else if (deadlined_Task != string::npos){
			size_t get_date = input.find("/");
			_TaskType = DEADLINE_Task_LABEL;
			_deadlineTime = input.substr(deadlined_Task + 4, 5);
			if (get_date != string::npos){
				_deadlineDate = input.substr(get_date - 2, 5);
			}
		}
	}
	checkInputValidation();
}

void Task::MarkDone(){
	_status = "done";
}

void Task::MarkUndone(){
	_status = "processing";
}

void Task::checkInputValidation(){
	//check for valid time frame
	bool valid_time = false;
	int start_hour; //deadline Task use this to store time
	int start_mins; //deadline Task use this to store time
	int end_hour;
	int end_mins;

	//check time frame in scheduled Task
	while ((_TaskType == SCHEDULED_Task_LABEL) && (!valid_time)){
		size_t get__startTime = _startTime.find(":");
		size_t get__endTime = _endTime.find(":");
		start_hour = atoi(_startTime.substr(0, get__startTime).c_str());
		start_mins = atoi(_startTime.substr(get__startTime + 1, 2).c_str());
		end_hour = atoi(_endTime.substr(0, get__endTime).c_str());
		end_mins = atoi(_endTime.substr(get__endTime + 1, 2).c_str());
		if ((start_hour >= 0 && start_hour <= 24) && (start_mins >= 0 && start_mins <= 60) && (end_hour >= 0 && end_hour <= 24) && (end_mins >= 0 && end_mins <= 60)){
			if (start_hour < end_hour){
				valid_time = true;
			}
			else{
				cout << INVALID_TIME_MSG << endl;
				cout << "starting time:";
				cin >> _startTime;
				cout << "ending time:";
				cin >> _endTime;
			}
		}
		else{
			cout << INVALID_TIME_MSG << endl;
			cout << "starting time:";
			cin >> _startTime;
			cout << "ending time:";
			cin >> _endTime;
		}
	}

	//check time frame in deadline Task
	while ((_TaskType == DEADLINE_Task_LABEL) && (!valid_time)){
		size_t get_time = _deadlineTime.find(":");
		start_hour = atoi(_deadlineTime.substr(0, get_time).c_str());
		start_mins = atoi(_deadlineTime.substr(get_time + 1, 2).c_str());
		if ((start_hour >= 0 && start_hour <= 24) && (start_mins >= 0 && start_mins <= 60)){
			valid_time = true;
		}
		else{
			cout << INVALID_TIME_MSG << endl;
			cout << "deadline time:";
			cin >> _deadlineTime;
		}
	}

	//check for valid date
	bool valid_date = false;
	int month;
	int date;

	//check date for deadline Task
	while ((_TaskType == DEADLINE_Task_LABEL) && (!valid_date)){
		size_t get_date = _deadlineDate.find("/");
		date = atoi(_deadlineDate.substr(0, get_date).c_str());
		month = atoi(_deadlineDate.substr(get_date + 1, 2).c_str());
		if ((date >= 1 && date <= 31) && (month >= 1 && month <= 12)){
			valid_date = true;
		}
		else{
			cout << INVALID_DATE_MSG << endl;
			cin >> _deadlineDate;
		}
	}

	//check date for schedule Task
	while ((_TaskType == SCHEDULED_Task_LABEL) && (!valid_date)){
		size_t get_date = _scheduledDate.find("/");
		date = atoi(_scheduledDate.substr(0, get_date).c_str());
		month = atoi(_scheduledDate.substr(get_date + 1, 2).c_str());
		if ((date >= 1 && date <= 31) && (month >= 1 && month <= 12)){
			valid_date = true;
		}
		else{
			cout << INVALID_DATE_MSG << endl;
			cin >> _scheduledDate;
		}
	}
}

