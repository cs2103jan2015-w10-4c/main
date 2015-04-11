#include "Parser.h"

const int Task_LEN = 250;
const string SCHEDULED_TASK_LABEL = "timed";
const string DEADLINE_TASK_LABEL = "deadline";
const string FLOATING_TASK_LABEL = "floating";
const string PROCESSING_TASK_LABEL = "progressing";
const string FINISHED_TASK_LABEL = "done";
const string UNCOMPLETED_TASK_LABEL = "uncompleted";
const string MESSAGE_INVALID_DATE = "Invalid date, provide valid date";
const string MESSAGE_INVALID_TIME = "Invalid time, provide valid time";
const string MARK_FROM = "-from";
const string MARK_TO = "-to";
const string MARK_BY = "-by";
const string MARK_AT = "@";
const string SLASH = "/";
const string COLON = ":";
const string EMPTY_SPACE =" ";
const int LENGTH_OF_DATE = 5;

Task::Task(){}

Task::Task(string input){
	if (!input.empty()){
		size_t timedTask = input.find(MARK_FROM);
		size_t timedTaskEnd = input.find(MARK_TO);
		size_t deadlinedTask = input.find(MARK_BY);
		size_t venueTask = input.find(MARK_AT);
		
		if((timedTask != string::npos && timedTaskEnd == string::npos) || (timedTask == string::npos && timedTaskEnd != string::npos) || (timedTask > timedTaskEnd)){
			isValid = false;
		}

		if (timedTask != string::npos && timedTaskEnd != string::npos){
			if((input.substr(timedTaskEnd, venueTask-timedTaskEnd)).find(SLASH) == string::npos){
				isValid = false;
			}
			else{
				isValid = true;
				DateParser parseDate(input.substr(timedTaskEnd));
				TimeParser parseTime(input.substr(timedTask));

				_TaskType = SCHEDULED_TASK_LABEL;
				_TaskName = input.substr(0, timedTask - 1);
				_startTime = parseTime.getStartTime();
				_endTime = parseTime.getEndTime();
				_deadlineTime = "";
				_scheduledDate = parseDate.getDate();
				_deadlineDate = "";
				_integerDay = parseDate.getDay();
				_integerMonth = parseDate.getMonth();
				_startHour = parseTime.getStartHour();
				_startMinute = parseTime.getStartMinute();
				_endHour = parseTime.getEndHour();
				_endMinute = parseTime.getEndMinute();
				_alphaMonth = parseDate.getAlphaMonth();
				_scheduledDateReverse = parseDate.getDateReverse();
			}	
		}
	    if (deadlinedTask != string::npos){
			isValid = true;
			DateParser parseDate(input);
			TimeParser parseTime(input);

			_TaskType = DEADLINE_TASK_LABEL;
			_TaskName = input.substr(0, deadlinedTask - 1);
			_startTime = "";
			_endTime = "";
			_deadlineTime = input.substr(deadlinedTask + 4, 5);
			_startHour = parseTime.getStartHour();
			_startMinute = parseTime.getStartMinute();
			_scheduledDate = "";
			_deadlineDate = parseDate.getDate();
			_integerDay = parseDate.getDay();
			_integerMonth = parseDate.getMonth();
			_alphaMonth = parseDate.getAlphaMonth();
		}
		if(timedTask == string::npos && timedTaskEnd == string::npos && deadlinedTask == string::npos) {
			isValid = true;
			_TaskType = FLOATING_TASK_LABEL;
			_TaskName = input;
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledDate = "";
			_deadlineDate = "";
			_scheduledDateReverse = "";
			
		}
		_status = PROCESSING_TASK_LABEL;
		if (venueTask != string::npos){
			VenueParser parseVenue(input);
		    _venue = parseVenue.getVenue();
		}
		else{
			_venue = "";
		}
	}
	
	checkInputValidation();
}

Task::~Task(){}

Task::Task(string Task, string input){
	if (!Task.empty()){

		//store _status
		size_t find__status = Task.find(PROCESSING_TASK_LABEL);
		if (find__status != string::npos){
			_status = PROCESSING_TASK_LABEL;
		}
		else{
			size_t find__status = Task.find(FINISHED_TASK_LABEL);
			if (find__status != string::npos){
				_status = FINISHED_TASK_LABEL;
			}
			else{
				_status = EMPTY_SPACE;
			}
		}

		//classify Tasks into scheduled, deadlined or floating
		size_t find_bracket = Task.find("[");
		string temp;	//to store remaining part of the Task arguement to check whether there is a time included there
		if (find_bracket != string::npos){	//date found, Task is either scheduled or deadlined.
			//assume double digit date
				


			size_t find_time = Task.find(":"); 
			temp = Task.substr(find_time + 2);
			size_t find_ending_time = temp.find(":");	//check if there's an ending time ie. seperate deadlined Task and scheduled Task

			if ((find_time != string::npos) && (find_ending_time != string::npos)){
				TimeParser parseTime(Task);
				DateParser parseDate(Task);

				_TaskType = SCHEDULED_TASK_LABEL;
				_TaskName = Task.substr(0, find_bracket - 1);
				_startTime = parseTime.getStartTime();
				_endTime = parseTime.getEndTime();
				_deadlineTime = "";
				_scheduledDate = parseDate.getDate();
				_deadlineDate = "";
				_startHour = parseTime.getStartHour();
			    _startMinute = parseTime.getStartMinute();
			    _endHour = parseTime.getEndHour();
			    _endMinute = parseTime.getEndMinute();
				_scheduledDateReverse = parseDate.getDateReverse();
				_integerDay = parseDate.getDay();
			    _integerMonth = parseDate.getMonth();
			    _alphaMonth = parseDate.getAlphaMonth();
			}
			else if (find_time != string::npos){
				DateParser parseDate(Task);
				TimeParser parseTime(Task);

				_TaskName = Task.substr(0, find_bracket - 2);
				_TaskType = DEADLINE_TASK_LABEL;
				_startTime = "";
				_endTime = "";
				_deadlineTime = parseTime.getStartTime();
				_scheduledDate = "";
				_deadlineDate = parseDate.getDate();
				_venue = "";
			}

		}
		else{
			_TaskType = FLOATING_TASK_LABEL;
			_TaskName = Task.substr(0, find__status-2);
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledDate = "";
			_deadlineDate = "";
			_scheduledDateReverse = "";
		}
		size_t venueTask = Task.find(MARK_AT);
		size_t status_mark = Task.find_last_of(EMPTY_SPACE);
		if (venueTask != string::npos){
			VenueParser parseVenue(Task);
			string tempVenue;
			tempVenue = parseVenue.getVenue();
			
			_venue = tempVenue.substr(0, status_mark - venueTask);
		}
		else{
			_venue = "";
		}
	}
	checkInputValidation();
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

	input = EMPTY_SPACE + input;
	if(!input.empty()) {
		size_t timedTask_startTime = input.find("-from");
		size_t timedTask_endTime = input.find("-to");
		size_t deadlinedTask = input.find("-by");
		size_t date = input.find("/");
		size_t venue = input.find("@");

		if(timedTask_startTime!=string::npos){
			_startTime = input.substr(timedTask_startTime + 6, 5);
			TimeParser updateInfo(input);
			_startHour = updateInfo.getStartHour();
			_startMinute = updateInfo.getStartMinute();
		}

		if(timedTask_endTime!=string::npos){
			_endTime = input.substr(timedTask_endTime + 4, 5);
			TimeParser updateInfo(input);
			_endHour = updateInfo.getEndHour();
			_endMinute = updateInfo.getEndMinute();
		}

		if(deadlinedTask!=string::npos){
				_deadlineTime = input.substr(deadlinedTask + 4, 5);
				TimeParser updateInfo(input);
				_startHour = updateInfo.getStartHour();
				_startMinute = updateInfo.getStartMinute();
		}
		if(date!=string::npos){
			if(_TaskType==SCHEDULED_TASK_LABEL){
				DateParser dateParse(input);
				_scheduledDate = dateParse.getDate();
				_integerDay = dateParse.getDay();
				_integerMonth = dateParse.getMonth();
			}
			else if(_TaskType==DEADLINE_TASK_LABEL){
				DateParser dateParse(input);
				_deadlineDate = dateParse.getDate();
				_integerDay = dateParse.getDay();
				_integerMonth = dateParse.getMonth();
			}
		}
		if(venue!=string::npos){
			_venue = input.substr(venue);
		}

		string temp;
		if(timedTask_endTime==string::npos){
			if(timedTask_startTime==string::npos){
				if(deadlinedTask==string::npos){
					if(date==string::npos){
						if(venue == string::npos){
							temp = input;
							_TaskName = temp;
						}
					}
				}
			}
		}
		if(deadlinedTask!=string::npos){
			temp = input.substr(0,deadlinedTask);
			if(temp!=EMPTY_SPACE){
				_TaskName = temp;
			}
		}else if(timedTask_startTime!=string::npos){
			temp = input.substr(0,timedTask_startTime);
			if(temp!=EMPTY_SPACE){
				_TaskName = temp;
			}
		}else if(timedTask_endTime!=string::npos){
			temp = input.substr(0,timedTask_endTime);
			if(temp!=EMPTY_SPACE){
				_TaskName = temp;
			}
		}else if(date!=string::npos){
			if(_TaskType==SCHEDULED_TASK_LABEL){
				size_t temparory = input.find_first_of(_scheduledDate);
				if(temparory!=0){
					temp = input.substr(0,temparory);
					if(temp!=EMPTY_SPACE){
					_TaskName = temp;
					}
				}
				
			}
			else if(_TaskType==DEADLINE_TASK_LABEL){
				size_t temparory = input.find_first_of(_deadlineDate);
				if(temparory!=0){
					temp = input.substr(0,temparory);
					if(temp!=EMPTY_SPACE){
					_TaskName = temp;
					}
				}
				
			}
		}else if(venue!=string::npos){
			temp = input.substr(0,venue);
			if(temp!=EMPTY_SPACE){
				_TaskName = temp;
			}
		}
		
	}
	checkInputValidation();
	
}



void Task::MarkDone(){
	_status = FINISHED_TASK_LABEL;
}

void Task::MarkUndone(){
	_status = PROCESSING_TASK_LABEL;
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
		start_hour = _startHour;
		start_mins = _startMinute;
		end_hour = _endHour;
		end_mins = _endMinute;
		if ((start_hour >= 0 && start_hour <= 24) && (start_mins >= 0 && start_mins <= 60) && (end_hour >= 0 && end_hour <= 24) && (end_mins >= 0 && end_mins <= 60)){
			if (start_hour < end_hour){
				valid_time = true;
			}
			else{
				cout << MESSAGE_INVALID_TIME << endl;
				cout << "starting time:";
				getline (cin, _startTime);
				cout << "ending time:";
				getline(cin,_endTime);
			}
		}
		else{
			cout << MESSAGE_INVALID_TIME << endl;
			cout << "starting time:";
			getline (cin, _startTime);
			cout << "ending time:";
			getline(cin,_endTime);
		}
	}

	//check time frame in deadline Task
	while ((_TaskType == DEADLINE_TASK_LABEL) && (!valid_time)){
		size_t get_time = _deadlineTime.find(COLON);
		start_hour = _startHour;
		start_mins = _startMinute;
		if ((start_hour >= 0 && start_hour <= 24) && (start_mins >= 0 && start_mins <= 60)){
			valid_time = true;
		}
		else{
			cout << MESSAGE_INVALID_TIME << endl;
			cout << "deadline time:";
			getline (cin ,_deadlineTime);
		}
	}

	//check for valid date
	bool valid_date = false;
	int month;
	int date;

	//check date for deadline Task
	while ((_TaskType == DEADLINE_TASK_LABEL) && (!valid_date)){
		size_t get_date = _deadlineDate.find(SLASH);
		
		if (get_date != string::npos){
			date = _integerDay;
			month = _integerMonth;
		    if ((date >= 1 && date <= 31) && (month >= 1 && month <= 12)){
			    valid_date = true;
		    }
		    else{
			    cout << MESSAGE_INVALID_DATE <<endl;
			    getline(cin,_deadlineDate);
		    }
		}
	}

	//check date for schedule Task
	while ((_TaskType == SCHEDULED_TASK_LABEL) && (!valid_date)){
		size_t get_date = _scheduledDate.find(SLASH);
		if(get_date != string::npos){
			date = atoi(_scheduledDate.substr(0, get_date).c_str());
		    month = atoi(_scheduledDate.substr(get_date + 1, 2).c_str());
		    if ((date >= 1 && date <= 31) && (month >= 1 && month <= 12)){
			    valid_date = true;
		    }
		    else{
			    cout << MESSAGE_INVALID_DATE << endl;
			    getline(cin, _scheduledDate);
		    }
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
/*
bool Task::isValid(){
	return _isValid;
}*/