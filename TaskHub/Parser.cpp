#include "Parser.h"

const int Task_LEN = 250;
const string SCHEDULED_Task_LABEL = "timed";
const string DEADLINE_Task_LABEL = "deadline";
const string FLOATING_Task_LABEL = "floating";
const string PROCESSING_Task_LABEL = "progressing";
const string FINISHED_Task_LABEL = "done";
const string INVALID_DATE_MSG = "invalid date, provide valid date";
const string INVALID_TIME_MSG = "invalid time, provide valid time";
const string EMPTY_SPACE =" ";
const int LENGTH_OF_DATE = 5;

Task::Task(){}

Task::Task(string input){
	
	if (!input.empty()){
		size_t timed_TaskStart = input.find("-from");
		size_t time_TaskEnd = input.find("-to");
		size_t deadlined_Task = input.find("-by");
		size_t venue_Task = input.find("@");
		size_t timed_startDate = input.substr(timed_TaskStart).find_first_of("/");
		size_t timed_endDate = input.substr(timed_TaskEnd).find_first_of("/");
		if (timed_TaskStart != string::npos){
			 
		     TimeParser parseTime(input.substr(timed_TaskStart));
		
			_TaskType = SCHEDULED_Task_LABEL;
			_TaskName = input.substr(0, timed_TaskStart - 1);
			_startTime = parseTime.getStartTime();
			_endTime = parseTime.getEndTime();
			_deadlineTime = "";
			_deadlineDate = "";
			_startHour = parseTime.getStartHour();
			_startMinute = parseTime.getStartMinute();
			_endHour = parseTime.getEndHour();
			_endMinute = parseTime.getEndMinute();
			
			if(timed_startDate != string::npos && timed_startDate == timed_endDate){
				DateParser parseDate(input.substr(timed_TaskStart));
				_scheduledStartDate = parseDate.getDate();
			    _scheduledEndDate = "";
				_scheduledDateReverse = parseDate.getDateReverse();
				_integerStartDay = parseDate.getDay();
				_integerStartMonth = parseDate.getMonth();
				_alphaMonth = parseDate.getAlphaMonth();
				
			}
			else if(timed_startDate != string::npos && timed_startDate != timed_endDate){
				DateParser parseStartDate(input.substr(timed_TaskStart+6, LENGTH_OF_DATE));
				DateParser parseEndDate(input.substr(time_TaskEnd+6, LENGTH_OF_DATE));
				_scheduledStartDate = parseStartDate.getDate();
				_scheduledEndDate = parseEndDate.getDate();
				_scheduledDateReverse = parseStartDate.getDateReverse();
				_integerStartDay = parseStartDate.getDay();
				_integerStartMonth = parseStartDate.getMonth();
				_alphaMonth = parseStartDate.getAlphaMonth();
				_integerEndDay = parseEndDate.getDay();
				_integerEndMonth = parseEndDate.getMonth();
			}

		}
		else if (deadlined_Task != string::npos){
			DateParser parseDate(input.substr(deadlined_Task));

			_TaskType = DEADLINE_Task_LABEL;
			_TaskName = input.substr(0, deadlined_Task - 1);
			_startTime = "";
			_endTime = "";
			_deadlineTime = input.substr(deadlined_Task + 4, 5);
			_scheduledStartDate = "";
			_scheduledEndDate = "";
			_deadlineDate = parseDate.getDate();
			_startHour = atoi(_deadlineTime.substr(0,2).c_str());
			_startMinute = atoi(_deadlineTime.substr(3,2).c_str());
			_integerStartDay = parseDate.getDay();
			_integerStartMonth = parseDate.getMonth();
			_alphaMonth = parseDate.getAlphaMonth();
		}
		else{
			_TaskType = FLOATING_Task_LABEL;
			_TaskName = input;
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledStartDate = "";
			_scheduledEndDate = "";
			_deadlineDate = "";
			
		}
		_status = "progressing";
		if (venue_Task != string::npos){
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
		size_t find_bracket = Task.find_last_of("[");
		size_t find_bracketEnd = Task.find_last_of("]");
		size_t find_startDate = Task.substr(find_bracket).find_first_of("/");
		size_t find_endDate = Task.substr(find_bracket, find_bracketEnd - find_bracket).find_last_of("/");
		string temp_date;
		string temp;	//to store remaining part of the Task arguement to check whether there is a time included there
		if (find_startDate != string::npos && find_startDate == find_endDate){	//only start date is found, Task is either scheduled or deadlined.
			//assume double digit date
				temp_date = Task.substr(find_startDate - 2, 5);


			size_t find_time = Task.find(":"); 
			temp = Task.substr(find_time + 2);
			size_t find_ending_time = temp.find(":");	//check if there's an ending time ie. seperate deadlined Task and scheduled Task

			if ((find_time != string::npos) && (find_ending_time != string::npos)){
				
				size_t find_bracket = Task.find_first_of("[");
				TimeParser parseTime(Task.substr(find_bracket));
				_TaskName = Task.substr(0, find_bracket-1);
				_TaskType = SCHEDULED_Task_LABEL;
				_startTime = Task.substr(find_time - 2, 5);
				_endTime = temp.substr(find_ending_time - 2, 5);
				_deadlineTime = "";
				_deadlineDate = "";
			    _startHour = parseTime.getStartHour();
			    _startMinute = parseTime.getStartMinute();
			    _endHour = parseTime.getEndHour();
			    _endMinute = parseTime.getEndMinute();
				
				if(find_startDate != string::npos && find_startDate == find_endDate){
					DateParser parseDate(Task.substr(find_bracket));
					_scheduledStartDate = parseDate.getDate();
					_scheduledDateReverse = parseDate.getDateReverse();
					_scheduledEndDate = "";
					_integerStartDay = parseDate.getDay();
			        _integerStartMonth = parseDate.getMonth();
					_alphaMonth = parseDate.getAlphaMonth();
				}
				else if(find_startDate != string::npos && find_startDate != find_endDate){
					temp = Task.substr(find_bracket);
					size_t find_dash = temp.find("-");
					DateParser parseStartDate(temp);
					DateParser parseEndDate(temp.substr(find_dash));
					_scheduledStartDate = parseStartDate.getDate();
					_scheduledDateReverse = parseStartDate.getDateReverse();
					_scheduledEndDate = parseEndDate.getDate();
					_integerStartDay = parseStartDate.getDay();
			        _integerStartMonth = parseStartDate.getMonth();
					_integerEndDay = parseEndDate.getDay();
					_integerEndMonth = parseEndDate.getMonth();
					_alphaMonth = parseStartDate.getAlphaMonth();
				}


			}
			else if (find_time != string::npos){
				size_t find_bracket = Task.find_first_of("[");
				DateParser parseDate(Task.substr(find_bracket));
				_TaskName = Task.substr(0, find_bracket-1);
				_TaskType = DEADLINE_Task_LABEL;
				_startTime = "";
				_endTime = "";
				_deadlineTime = Task.substr(find_time - 2, 5);
				_scheduledStartDate = "";
				_scheduledEndDate = "";
				_deadlineDate = temp_date;
				_startHour = atoi(_deadlineTime.substr(0,2).c_str());
			    _startMinute = atoi(_deadlineTime.substr(3,2).c_str());
			    _integerStartDay = parseDate.getDay();
			    _integerStartMonth = parseDate.getMonth();
				_alphaMonth = parseDate.getAlphaMonth();
			}

		}

		else{
			_TaskType = FLOATING_Task_LABEL;
			_TaskName = Task.substr(0, find__status - 2);
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledStartDate = "";
			_scheduledEndDate = "";
			_deadlineDate = "";
		}
		size_t venue_Task = Task.find("@");
		size_t status_mark = Task.find_last_of(" ");
		if (venue_Task != string::npos){
			VenueParser parseVenue(Task);
			string tempVenue;
			tempVenue = parseVenue.getVenue();
			
			_venue = tempVenue.substr(0, status_mark - venue_Task);
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
	if (_TaskType == DEADLINE_Task_LABEL){
		output = Task+EMPTY_SPACE+" [due "+_deadlineDate.c_str()+" "+_deadlineTime.c_str()+"] "+_venue.c_str()+" "+ _status.c_str();
	}
	else if (_TaskType == SCHEDULED_Task_LABEL){
		output = Task+EMPTY_SPACE+"[ "+ _scheduledStartDate.c_str()+" "+_startTime.c_str()+" - "+ _scheduledEndDate.c_str() +" " + _endTime.c_str()+" ] "+_venue.c_str()+" "+ _status.c_str();
	}
	else if (_TaskType == FLOATING_Task_LABEL){
		output = Task+EMPTY_SPACE+_venue.c_str()+" "+_status.c_str();
	}
	return output;
}

string Task::getTaskName(){
	return _TaskName;
}

void Task::UpdateTask(string input){

	input = " " + input;
	if(!input.empty()) {
		size_t timed_Task_startTime = input.find("-from");
		size_t timed_Task_endTime = input.find("-to");
		size_t deadlined_Task = input.find("-by");
		size_t date = input.find("/");
		size_t venue = input.find("@");

		if(timed_Task_startTime!=string::npos){
			_startTime = input.substr(timed_Task_startTime + 6, 5);
			TimeParser updateInfo(input);
			_startHour = updateInfo.getStartHour();
			_startMinute = updateInfo.getStartMinute();
		}

		if(timed_Task_endTime!=string::npos){
			_endTime = input.substr(timed_Task_endTime + 4, 5);
			TimeParser updateInfo(input);
			_endHour = updateInfo.getEndHour();
			_endMinute = updateInfo.getEndMinute();
		}

		if(deadlined_Task!=string::npos){
				_deadlineTime = input.substr(deadlined_Task + 4, 5);
				TimeParser updateInfo(input);
				_startHour = updateInfo.getStartHour();
				_startMinute = updateInfo.getStartMinute();
		}
		if(date!=string::npos){
			if(_TaskType==SCHEDULED_Task_LABEL){
				DateParser dateParse(input);
				_scheduledStartDate = dateParse.getDate();
				_integerStartDay = dateParse.getDay();
				_integerStartMonth = dateParse.getMonth();
			}
			else if(_TaskType==DEADLINE_Task_LABEL){
				DateParser dateParse(input);
				_deadlineDate = dateParse.getDate();
				_integerStartDay = dateParse.getDay();
				_integerStartMonth = dateParse.getMonth();
			}
		}
		if(venue!=string::npos){
			_venue = input.substr(venue);
		}

		string temp;
		if(timed_Task_endTime==string::npos){
			if(timed_Task_startTime==string::npos){
				if(deadlined_Task==string::npos){
					if(date==string::npos){
						if(venue == string::npos){
							temp = input;
							_TaskName = temp;
						}
					}
				}
			}
		}
		if(deadlined_Task!=string::npos){
			temp = input.substr(0,deadlined_Task);
			if(temp!=" "){
				_TaskName = temp;
			}
		}else if(timed_Task_startTime!=string::npos){
			temp = input.substr(0,timed_Task_startTime);
			if(temp!=" "){
				_TaskName = temp;
			}
		}else if(timed_Task_endTime!=string::npos){
			temp = input.substr(0,timed_Task_endTime);
			if(temp!=" "){
				_TaskName = temp;
			}
		}else if(date!=string::npos){
			if(_TaskType==SCHEDULED_Task_LABEL){
				size_t temparory = input.find_first_of(_scheduledStartDate);
				if(temparory!=0){
					temp = input.substr(0,temparory);
					if(temp!=" "){
					_TaskName = temp;
					}
				}
				
			}
			else if(_TaskType==DEADLINE_Task_LABEL){
				size_t temparory = input.find_first_of(_deadlineDate);
				if(temparory!=0){
					temp = input.substr(0,temparory);
					if(temp!=" "){
					_TaskName = temp;
					}
				}
				
			}
		}else if(venue!=string::npos){
			temp = input.substr(0,venue);
			if(temp!=" "){
				_TaskName = temp;
			}
		}
		
	}
	checkInputValidation();
	
}



void Task::MarkDone(){
	_status = "done";
}

void Task::MarkUndone(){
	_status = "progressing";
}

void Task::markUncompleted(){
	_status = "uncompleted";
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
				getline (cin, _startTime);
				cout << "ending time:";
				getline(cin,_endTime);
			}
		}
		else{
			cout << INVALID_TIME_MSG << endl;
			cout << "starting time:";
			getline (cin, _startTime);
			cout << "ending time:";
			getline(cin,_endTime);
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
			getline (cin ,_deadlineTime);
		}
	}

	//check for valid date
	bool valid_date = false;
	int month;
	int date;

	//check date for deadline Task
	while ((_TaskType == DEADLINE_Task_LABEL) && (!valid_date)){
		size_t get_date = _deadlineDate.find("/");
		
		if (get_date != string::npos){
			date = atoi(_deadlineDate.substr(0, get_date).c_str());
		    month = atoi(_deadlineDate.substr(get_date + 1, 2).c_str());
		    if ((date >= 1 && date <= 31) && (month >= 1 && month <= 12)){
			    valid_date = true;
		    }
		    else{
			    cout << INVALID_DATE_MSG <<endl;
			    getline(cin,_deadlineDate);
		    }
		}
	}

	//check date for schedule Task
	while ((_TaskType == SCHEDULED_Task_LABEL) && (!valid_date)){
		size_t get_date = _scheduledStartDate.find("/");
		if(get_date != string::npos){
			date = atoi(_scheduledStartDate.substr(0, get_date).c_str());
		    month = atoi(_scheduledStartDate.substr(get_date + 1, 2).c_str());
		    if ((date >= 1 && date <= 31) && (month >= 1 && month <= 12)){
			    valid_date = true;
		    }
		    else{
			    cout << INVALID_DATE_MSG << endl;
			    getline(cin, _scheduledStartDate);
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

string Task::getScheduledStartDate(){
	return _scheduledStartDate;
}

string Task::getScheduledEndDate(){
	return _scheduledEndDate;
}

string Task::getScheduledStartDateReverse(){
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

int Task::getIntegerStartDay(){
	return _integerStartDay;
}

int Task::getIntegerStartMonth(){
	return _integerStartMonth;
}

int Task::getIntegerEndDay(){
	return _integerEndDay;
}

int Task::getIntegerEndMonth(){
	return _integerEndMonth;
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
