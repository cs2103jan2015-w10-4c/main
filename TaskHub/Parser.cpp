#include "Parser.h"

const int Textbody_LEN = 250;
const string SCHEDULED_Textbody_LABEL = "timed";
const string DEADLINE_Textbody_LABEL = "deadline";
const string FLOATING_Textbody_LABEL = "floating";
const string PROCESSING_Textbody_LABEL = "progressing";
const string FINISHED_Textbody_LABEL = "done";
const string INVALID_DATE_MSG = "invalid date, provide valid date";
const string INVALID_TIME_MSG = "invalid time, provide valid time";

Textbody::Textbody(){}

Textbody::Textbody(string input){
	if (!input.empty()){
		size_t timed_Textbody = input.find("-from");
		size_t deadlined_Textbody = input.find("-by");

		if (timed_Textbody != string::npos){
			size_t ending_time = input.find("-to");
			size_t get_date = input.find("/");
			_TextbodyType = SCHEDULED_Textbody_LABEL;

			_TextbodyName = input.substr(0, timed_Textbody - 1);
			_startTime = input.substr(timed_Textbody + 6, 5);
			_endTime = input.substr(ending_time + 4, 5);
			_deadlineTime = "";
			_scheduledDate = input.substr(get_date - 2, 5);
			_deadlineDate = "";
		}
		else if (deadlined_Textbody != string::npos){
			size_t get_date = input.find("/");
			_TextbodyType = DEADLINE_Textbody_LABEL;
			_TextbodyName = input.substr(0, deadlined_Textbody - 1);
			_startTime = "";
			_endTime = "";
			_deadlineTime = input.substr(deadlined_Textbody + 4, 5);
			_scheduledDate = "";
			_deadlineDate = input.substr(get_date - 2, 5);
		}
		else{
			_TextbodyType = FLOATING_Textbody_LABEL;
			_TextbodyName = input;
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledDate = "";
			_deadlineDate = "";
			
		}
		_status = "progressing";
	}
	checkInputValidation();
}

Textbody::~Textbody(){}

Textbody::Textbody(string Textbody, string input){
	if (!Textbody.empty()){

		//store _status
		size_t find__status = Textbody.find("progressing");
		if (find__status != string::npos){
			_status = "progressing";
		}
		else{
			size_t find__status = Textbody.find("done");
			if (find__status != string::npos){
				_status = "done";
			}
			else{
				_status = " ";
			}
		}

		//classify Textbodys into scheduled, deadlined or floating
		size_t find_date = Textbody.find("/");
		string temp_date;
		string temp;	//to store remaining part of the Textbody arguement to check whether there is a time included there
		if (find_date != string::npos){	//date found, Textbody is either scheduled or deadlined.
			//assume double digit date
				_TextbodyName = Textbody.substr(0, find_date - 2);
				temp_date = Textbody.substr(find_date - 2, 5);


			size_t find_time = Textbody.find(":"); 
			temp = Textbody.substr(find_time + 2);
			size_t find_ending_time = temp.find(":");	//check if there's an ending time ie. seperate deadlined Textbody and scheduled Textbody

			if ((find_time != string::npos) && (find_ending_time != string::npos)){
				_TextbodyType = SCHEDULED_Textbody_LABEL;
				_startTime = Textbody.substr(find_time - 2, 5);
				_endTime = temp.substr(find_ending_time - 2, 5);
				_deadlineTime = "";
				_scheduledDate = temp_date;
				_deadlineDate = "";
			}
			else if (find_time != string::npos){
				_TextbodyType = DEADLINE_Textbody_LABEL;
				_startTime = "";
				_endTime = "";
				_deadlineTime = Textbody.substr(find_time - 2, 5);
				_scheduledDate = "";
				_deadlineDate = temp_date;
			}

		}
		else{
			_TextbodyType = FLOATING_Textbody_LABEL;
			_TextbodyName = Textbody.substr(0, find__status - 1);
			_startTime = "";
			_endTime = "";
			_deadlineTime = "";
			_scheduledDate = "";
			_deadlineDate = "";
		}
	}
	checkInputValidation();
}

string Textbody::ToString(){
	char Textbody[Textbody_LEN];
	strcpy_s(Textbody, _TextbodyName.c_str());
	if (_TextbodyType == DEADLINE_Textbody_LABEL){
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _deadlineDate.c_str());
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _deadlineTime.c_str());
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _status.c_str());
	}
	else if (_TextbodyType == SCHEDULED_Textbody_LABEL){
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _scheduledDate.c_str());
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _startTime.c_str());
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _endTime.c_str());
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _status.c_str());
	}
	else if (_TextbodyType == FLOATING_Textbody_LABEL){
		strcat_s(Textbody, " ");
		strcat_s(Textbody, _status.c_str());
	}
	return Textbody;
}

string Textbody::get_TextbodyName(){
	return _TextbodyName;
}

void Textbody::UpdateTextbody(string input){
	if (!input.empty()){
		size_t timed_Textbody = input.find("-from");
		size_t deadlined_Textbody = input.find("-by");
		if (timed_Textbody != string::npos){
			size_t ending_time = input.find("-to");
			size_t get_date = input.find("/");
			_TextbodyType = SCHEDULED_Textbody_LABEL;
			_startTime = input.substr(timed_Textbody + 6, 5);
			_endTime = input.substr(ending_time + 4, 5);
			if (get_date != string::npos){
				_scheduledDate = input.substr(get_date - 2, 5);
			}
		}
		else if (deadlined_Textbody != string::npos){
			size_t get_date = input.find("/");
			_TextbodyType = DEADLINE_Textbody_LABEL;
			_deadlineTime = input.substr(deadlined_Textbody + 4, 5);
			if (get_date != string::npos){
				_deadlineDate = input.substr(get_date - 2, 5);
			}
		}
	}
	checkInputValidation();
}

void Textbody::MarkDone(){
	_status = "done";
}

void Textbody::MarkUndone(){
	_status = "processing";
}

void Textbody::checkInputValidation(){
	//check for valid time frame
	bool valid_time = false;
	int start_hour; //deadline Textbody use this to store time
	int start_mins; //deadline Textbody use this to store time
	int end_hour;
	int end_mins;

	//check time frame in scheduled Textbody
	while ((_TextbodyType == SCHEDULED_Textbody_LABEL) && (!valid_time)){
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

	//check time frame in deadline Textbody
	while ((_TextbodyType == DEADLINE_Textbody_LABEL) && (!valid_time)){
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

	//check date for deadline Textbody
	while ((_TextbodyType == DEADLINE_Textbody_LABEL) && (!valid_date)){
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

	//check date for schedule Textbody
	while ((_TextbodyType == SCHEDULED_Textbody_LABEL) && (!valid_date)){
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