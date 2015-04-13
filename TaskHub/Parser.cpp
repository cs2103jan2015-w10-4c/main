//@author: A0115399W
//UpdateTask: @author A0115793Y
//updateTaskName: @author A0115793Y
#include <assert.h>
#include "Parser.h"


const int Task_LEN = 250;
const string SCHEDULED_TASK_LABEL = "timed";
const string DEADLINE_TASK_LABEL = "deadline";
const string FLOATING_TASK_LABEL = "floating";
const string PROGRESSING_TASK_LABEL = "progressing";
const string FINISHED_TASK_LABEL = "done";
const string UNCOMPLETED_TASK_LABEL = "uncompleted";
const string MESSAGE_INVALID_DATE = "Invalid date, provide valid date";
const string MESSAGE_INVALID_TIME = "Invalid time, provide valid time";
const string MESSAGE_START_TIME = "starting time:";
const string MESSAGE_END_TIME = "ending time:";
const string MESSAGE_DEADLINE_TIME = "deadline time:";
const string MARK_FROM = "-from";
const string MARK_TO = "-to";
const string MARK_BY = "-by";
const string MARK_AT = "@";
const string SLASH = "/";
const string COLON = ":";
const string EMPTY_SPACE =" ";
const string EMPTY_STRING = "";
const string BRACKET = "[";
const int ADJUSTMENT_ONE = 1;
const int ADJUSTMENT_FOUR = 4;
const int ADJUSTMENT_SIX= 6;
const int LENGTH_TIME = 2;
const int LENGTH_OF_TIME = 5;
const int LENGTH_OF_DATE = 5;
const int START_OF_STRING = 0;
const int HOUR_START = 0;
const int HOUR_END = 23;
const int MINUTE_START = 0;
const int MINUTE_END = 59;
const int MONTH_START = 1;
const int MONTH_END = 12;
const int DAY_START = 1;
const int FEB_END = 29;
const int DAY_30_END = 30;
const int DAY_31_END = 31;
const int FEB = 2;
const int APRIL = 4;
const int JUN = 6;
const int SEPT = 9;
const int NOV = 11;
Task::Task(){}

Task::Task(string input){
	if (!input.empty()){
		size_t timedTask = input.find(MARK_FROM);
		size_t timedTaskEnd = input.find(MARK_TO);
		size_t deadlinedTask = input.find(MARK_BY);
		size_t venueTask = input.find(MARK_AT);
		
		if (timedTask != string::npos && timedTaskEnd != string::npos && timedTaskEnd - timedTask == 12 && deadlinedTask == string::npos){
			string scheduledDateTime = input.substr(timedTask);
			size_t findScheduleDate = scheduledDateTime.find(SLASH);
			size_t findStartTime = scheduledDateTime.find_first_of(COLON);
			size_t findEndTime = scheduledDateTime.find_last_of(COLON);		
	
			if(findEndTime - findStartTime == 10 && findScheduleDate != string::npos && findScheduleDate > findEndTime){
				
		        DateParser parseDate(scheduledDateTime);
				TimeParser parseTime(scheduledDateTime);

				_TaskType = SCHEDULED_TASK_LABEL;
				_TaskName = input.substr(START_OF_STRING, timedTask - ADJUSTMENT_ONE);
				_startTime = parseTime.getStartTime();
				_endTime = parseTime.getEndTime();
				_deadlineTime = EMPTY_STRING;
				_scheduledDate = parseDate.getDate();
				_deadlineDate = EMPTY_STRING;
				_integerDay = parseDate.getDay();
				_integerMonth = parseDate.getMonth();
				_startHour = parseTime.getStartHour();
				_startMinute = parseTime.getStartMinute();
				_endHour = parseTime.getEndHour();
				_endMinute = parseTime.getEndMinute();
				_scheduledDateReverse = parseDate.getDateReverse();
			}
		}
		if (deadlinedTask != string::npos && timedTask == string::npos && timedTaskEnd == string::npos){
			string deadlineDateTime = input.substr(deadlinedTask);	
			size_t findDeadlineDate = deadlineDateTime.find(SLASH);
			size_t findStartTime = deadlineDateTime.find_first_of(COLON);
			size_t findEndTime = deadlineDateTime.find_last_of(COLON);

			if(findStartTime == findEndTime && findStartTime == 6 && findDeadlineDate != string::npos && findDeadlineDate > findStartTime){
				
				DateParser parseDate(deadlineDateTime);
				TimeParser parseTime(deadlineDateTime);

				_TaskType = DEADLINE_TASK_LABEL;
				_TaskName = input.substr(START_OF_STRING, deadlinedTask - ADJUSTMENT_ONE);
				_startTime = EMPTY_STRING;
				_endTime = EMPTY_STRING;
				_deadlineTime =	parseTime.getStartTime();
				_startHour = parseTime.getStartHour();
				_startMinute = parseTime.getStartMinute();
				_scheduledDate = EMPTY_STRING;
				_deadlineDate = parseDate.getDate();
				_integerDay = parseDate.getDay();
				_integerMonth = parseDate.getMonth();
			}
		}
		if(timedTask == string::npos && timedTaskEnd == string::npos && deadlinedTask == string::npos){
			_TaskType = FLOATING_TASK_LABEL;
			_TaskName = input;
			_startTime = EMPTY_STRING;
			_endTime = EMPTY_STRING;
			_deadlineTime = EMPTY_STRING;
			_scheduledDate = EMPTY_STRING;
			_deadlineDate = EMPTY_STRING;
			_scheduledDateReverse = EMPTY_STRING;
			
		}
		_status = PROGRESSING_TASK_LABEL;
		
		if (venueTask != string::npos){
			VenueParser parseVenue(input);
		    _venue = parseVenue.getVenue();
		}
		else{
			_venue = EMPTY_STRING;
		}
	}
		checkInputValidation();
}

Task::~Task(){}

Task::Task(string Task, string input){
	if (!Task.empty()){

		//store _status
		size_t find__status = Task.find(PROGRESSING_TASK_LABEL);
		if (find__status != string::npos){
			_status = PROGRESSING_TASK_LABEL;
		}
		else{
			 find__status = Task.find(FINISHED_TASK_LABEL);
			if (find__status != string::npos){
				_status = FINISHED_TASK_LABEL;
			}
			
			else{
				 find__status = Task.find(UNCOMPLETED_TASK_LABEL);
				if (find__status != string::npos){
					_status = UNCOMPLETED_TASK_LABEL;
				}
				else{
				_status = EMPTY_SPACE;
			    }
		   }
		}

		//classify Tasks into scheduled, deadlined or floating
		size_t find_bracket = Task.find(BRACKET);
		string temp;	//to store remaining part of the Task arguement to check whether there is a time included there
		if (find_bracket != string::npos){	//date found, Task is either scheduled or deadlined.
			//assume double digit date
				


			size_t find_time = Task.find(COLON); 
			temp = Task.substr(find_time + 2);
			size_t find_ending_time = temp.find(COLON);	//check if there's an ending time ie. seperate deadlined Task and scheduled Task

			if ((find_time != string::npos) && (find_ending_time != string::npos)){
				TimeParser parseTime(Task);
				DateParser parseDate(Task);
	
				_TaskType = SCHEDULED_TASK_LABEL;
				_TaskName = Task.substr(START_OF_STRING, find_bracket - ADJUSTMENT_ONE);
				_startTime = parseTime.getStartTime();
				_endTime = parseTime.getEndTime();
				_deadlineTime = EMPTY_STRING;
				_scheduledDate = parseDate.getDate();
				_deadlineDate = EMPTY_STRING;
				_startHour = parseTime.getStartHour();
			    _startMinute = parseTime.getStartMinute();
			    _endHour = parseTime.getEndHour();
			    _endMinute = parseTime.getEndMinute();
				_scheduledDateReverse = parseDate.getDateReverse();
				_integerDay = parseDate.getDay();
			    _integerMonth = parseDate.getMonth();
			    //_alphaMonth = parseDate.getAlphaMonth();
			}
			else if (find_time != string::npos){
				DateParser parseDate(Task);
				TimeParser parseTime(Task);

				_TaskName = Task.substr(START_OF_STRING, find_bracket - ADJUSTMENT_ONE);
				_TaskType = DEADLINE_TASK_LABEL;
				_startTime = EMPTY_STRING;
				_endTime = EMPTY_STRING;
				_deadlineTime = parseTime.getStartTime();
				_scheduledDate = EMPTY_STRING;
				_deadlineDate = parseDate.getDate();
				_venue = EMPTY_STRING;
			}

		}
		else{
			_TaskType = FLOATING_TASK_LABEL;
			if (Task.find(MARK_AT) == string::npos){
				_TaskName = Task.substr(START_OF_STRING, find__status);
			}
			else{
				_TaskName = Task.substr(START_OF_STRING, Task.find(MARK_AT));
			}
			_startTime = EMPTY_STRING;
			_endTime = EMPTY_STRING;
			_deadlineTime = EMPTY_STRING;
			_scheduledDate = EMPTY_STRING;
			_deadlineDate = EMPTY_STRING;
			_scheduledDateReverse = EMPTY_STRING;
		}
		size_t venueTask = Task.find(MARK_AT);
		size_t status_mark = Task.find_last_of(EMPTY_SPACE);
		if (venueTask != string::npos){
			VenueParser parseVenue(Task);
			string tempVenue;
			tempVenue = parseVenue.getVenue();
			
			_venue = tempVenue.substr(START_OF_STRING, status_mark - venueTask);
		}
		else{
			_venue = EMPTY_STRING;
		}
	}
	//checkInputValidation();
}

string Task::ToString(){
	char Task[Task_LEN];
	string output;
	strcpy_s(Task, _TaskName.c_str());
	if (_TaskType == DEADLINE_TASK_LABEL){
		output = Task+EMPTY_SPACE+" [due "+_deadlineDate.c_str()+EMPTY_SPACE+_deadlineTime.c_str()+"] "+_venue.c_str()+EMPTY_SPACE+ _status.c_str();
	}
	else if (_TaskType == SCHEDULED_TASK_LABEL){
		output = Task+EMPTY_SPACE+"[ "+ _scheduledDate.c_str()+EMPTY_SPACE+_startTime.c_str()+" - " + _endTime.c_str()+" ] "+_venue.c_str()+EMPTY_SPACE+ _status.c_str();
	}
	else if (_TaskType == FLOATING_TASK_LABEL){
		output = Task+EMPTY_SPACE+_venue.c_str()+EMPTY_SPACE+_status.c_str();
	}
	return output;
}

string Task::getTaskName(){
	return _TaskName;
}

void Task::UpdateTask(string input){
	input = EMPTY_SPACE+ input;

	if(!input.empty()) {
		size_t timed_Task_startTime = input.find(MARK_FROM);
		size_t timed_Task_endTime = input.find(MARK_TO);
		size_t deadlined_Task = input.find(MARK_BY);
		size_t date = input.find(SLASH);
		size_t venue = input.find(MARK_AT);
		
		//update starting time of scheduled task
		if(timed_Task_startTime!=string::npos) {
			_startTime = input.substr(timed_Task_startTime + ADJUSTMENT_SIX, LENGTH_OF_TIME);
			TimeParser updateInfo(input);
			_startHour = updateInfo.getStartHour();
			_startMinute = updateInfo.getStartMinute();
		}

		//update ending time of scheduled task
		if(timed_Task_endTime!=string::npos) {
			_endTime = input.substr(timed_Task_endTime + ADJUSTMENT_FOUR, LENGTH_OF_TIME);
			TimeParser updateInfo(input);
			_endHour = updateInfo.getEndHour();
			_endMinute = updateInfo.getEndMinute();
		}

		//update time of deadline task
		if(deadlined_Task!=string::npos) {
			_deadlineTime = input.substr(deadlined_Task + ADJUSTMENT_FOUR, LENGTH_OF_TIME);
			TimeParser updateInfo(input);
			_startHour = updateInfo.getStartHour();
			_startMinute = updateInfo.getStartMinute();
		}

		if(date!=string::npos) {
			//update date of scheudle dtask
			if(_TaskType==SCHEDULED_TASK_LABEL) {
				DateParser dateParse(input);
				_scheduledDate = dateParse.getDate();
				_integerDay = dateParse.getDay();
				_integerMonth = dateParse.getMonth();
			}
			//update date of deadline task
			else if(_TaskType==DEADLINE_TASK_LABEL) {
				DateParser dateParse(input);
				_deadlineDate = dateParse.getDate();
				_integerDay = dateParse.getDay();
				_integerMonth = dateParse.getMonth();
			}
		}
		//update venue
		if(venue!=string::npos) {
			_venue = input.substr(venue);
		}

		string temp;
		//task name case 1: only change task name  "update 1 meeting"
		if(timed_Task_endTime==string::npos) {
			if(timed_Task_startTime==string::npos) {
				if(deadlined_Task==string::npos) {
					if(date==string::npos) {
						if(venue == string::npos) {
							temp = input;
							_TaskName = temp;
						}
					}
				}
			}
		}
		//task name case 2 "update 1 meeting -by ..." 
		if(deadlined_Task!=string::npos) {
			temp = input.substr(0,deadlined_Task);
			updateTaskName(temp);
		}
		//task name case 3 "update 1 meeting -from ..
		else if(timed_Task_startTime!=string::npos) {
			temp = input.substr(0,timed_Task_startTime);
			updateTaskName(temp);
		}
		//task name case 4 "update 1 meeting -to..."
		else if(timed_Task_endTime!=string::npos) {
			temp = input.substr(0,timed_Task_endTime);
			updateTaskName(temp);
		}
		//task name case 5 "update 1 meeting 5/4"
		else if(date!=string::npos) {
			if(_TaskType==SCHEDULED_TASK_LABEL) {
				size_t temparory = input.find_first_of(_scheduledDate);
				if(temparory!=0) {
					temp = input.substr(0,temparory);
					updateTaskName(temp);
				}
			}
			else if(_TaskType==DEADLINE_TASK_LABEL) {
				size_t temparory = input.find_first_of(_deadlineDate);
				if(temparory!=0) {
					temp = input.substr(0,temparory);
					updateTaskName(temp);
				}
			}
		}
		//task name case 6 "update 1 meeting @biz"
		else if(venue!=string::npos) {
			temp = input.substr(START_OF_STRING,venue);
			updateTaskName(temp);
		}
	}
}
void Task::updateTaskName(string input){
	if(input!=EMPTY_SPACE){
		_TaskName = input;
	}
}

void Task::MarkDone(){
	_status = FINISHED_TASK_LABEL;
}

void Task::MarkUndone(){
	_status = PROGRESSING_TASK_LABEL;
}

void Task::markUncompleted(){
	_status = UNCOMPLETED_TASK_LABEL;
}

void Task::checkInputValidation(){
	//check for valid time frame
	bool valid_time = false;
	int start_hour; //deadline Task use this to store time
	int start_mins; //deadline Task use this to store time
	int end_hour;
	int end_mins;

	//check time frame in scheduled Task
	while ((_TaskType == SCHEDULED_TASK_LABEL) && (!valid_time)){
		size_t get__startTime = _startTime.find(COLON);
		size_t get__endTime = _endTime.find(COLON);
		start_hour = atoi(_startTime.substr(START_OF_STRING, get__startTime).c_str());
		start_mins = atoi(_startTime.substr(get__startTime + ADJUSTMENT_ONE, LENGTH_TIME).c_str());
		end_hour = atoi(_endTime.substr(START_OF_STRING, get__endTime).c_str());
		end_mins = atoi(_endTime.substr(get__endTime + ADJUSTMENT_ONE, LENGTH_TIME).c_str());
		if ((start_hour >= HOUR_START && start_hour <= HOUR_END) && (start_mins >= MINUTE_START && start_mins <= MINUTE_END) && (end_hour >= HOUR_START && end_hour <= HOUR_END) && (end_mins >= MINUTE_START && end_mins <= MINUTE_END)){
			if (start_hour <= end_hour && start_mins < end_mins){
				valid_time = true;
			}
			else{
				cout << MESSAGE_INVALID_TIME << endl;
				cout << MESSAGE_START_TIME;
				cin >> _startTime;
				cout << MESSAGE_END_TIME;
				cin >> _endTime;
			}
		}
		else{
			cout << MESSAGE_INVALID_TIME << endl;
			cout << MESSAGE_START_TIME;
			cin >> _startTime;
			cout << MESSAGE_END_TIME;
			cin >> _endTime;
		}
	}

	//check time frame in deadline Task
	while ((_TaskType == DEADLINE_TASK_LABEL) && (!valid_time)){
		size_t get_time = _deadlineTime.find(COLON);
		start_hour = atoi(_deadlineTime.substr(START_OF_STRING, get_time).c_str());
		start_mins = atoi(_deadlineTime.substr(get_time + ADJUSTMENT_ONE, LENGTH_TIME).c_str());
		if ((start_hour >= HOUR_START && start_hour <= HOUR_END) && (start_mins >= MINUTE_START && start_mins <= MINUTE_END)){
			valid_time = true;
		}
		else{
			cout << MESSAGE_INVALID_TIME << endl;
			cout << MESSAGE_DEADLINE_TIME;
			cin >> _deadlineTime;
		}
	}

	//check for valid date
	bool valid_date = false;
	int month;
	int date;

	//check date for deadline Task
	while ((_TaskType == DEADLINE_TASK_LABEL) && (!valid_date)){
		size_t get_date = _deadlineDate.find(SLASH);
		date = atoi(_deadlineDate.substr(START_OF_STRING, get_date).c_str());
		month = atoi(_deadlineDate.substr(get_date + ADJUSTMENT_ONE, LENGTH_TIME).c_str());
		if ((date >= DAY_START && date <= DAY_31_END) && (month >= MONTH_START && month <= MONTH_END)){
			valid_date = true;
		}
		else{
			cout << MESSAGE_INVALID_DATE << endl;
			cin >> _deadlineDate;
		}
	}

	//check date for schedule Task
	while ((_TaskType == SCHEDULED_TASK_LABEL) && (!valid_date)){
		size_t get_date = _scheduledDate.find(SLASH);
		date = atoi(_scheduledDate.substr(START_OF_STRING, get_date).c_str());
		month = atoi(_scheduledDate.substr(get_date + ADJUSTMENT_ONE, LENGTH_TIME).c_str());
		if ((date >= DAY_START && date <= DAY_31_END) && (month >= MONTH_START && month <= MONTH_END)){
			valid_date = true;
		}
		else{
			cout << MESSAGE_INVALID_DATE << endl;
			cin >> _scheduledDate;
		}
	}
}


string Task::getTaskType(){
	return _TaskType;
}

string Task::getStartTime(){
	return _startTime;
}

string Task::getEndTime(){
	return _endTime;
}

string Task::getDeadlineTime(){
	return _deadlineTime;
}

string Task::getScheduledDate(){
	return _scheduledDate;
}


string Task::getScheduledDateReverse(){
	return _scheduledDateReverse;
}

string Task::getDeadlineDate(){
	return _deadlineDate;
}

string Task::getStatus(){
	return _status;
}

string Task::getVenue(){
	return _venue;
}

int Task::getIntegerDay(){
	return _integerDay;
}

int Task::getIntegerMonth(){
	return _integerMonth;
}

int Task::getStartHour(){
	return _startHour;
}

int Task::getStartMinute(){
	return _startMinute;
}

int Task::getEndHour(){
	return _endHour;
}

int Task::getEndMinute(){
	return _endMinute;
}
