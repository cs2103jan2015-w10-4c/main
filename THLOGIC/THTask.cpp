#include <string>
#include <cassert>
#include "THTask.h"
#include "THTaskDueSoon.h"
#include "THUtility.h"

using namespace std;

THTask::THTask() {
	_isDone = false;
	_isOverdue = false;
	_isToday = false;
}

void THTask::setTaskName(string inputTaskName) {
	_taskName = inputTaskName;
}

void THTask::setStartingDate(string inputDate) {
	_StartingDate = inputDate;
}

void THTask::setStartingTime(string inputTime) {
	_StartingTime = inputTime;
}

void THTask::setEndingDate(string inputDate) {
	_EndingDate = inputDate;
}

void THTask::setEndingTime(string inputTime) {
	_EndingTime = inputTime;
}

void THTask::setStatus(bool inputStatus) {
	_isDone = inputStatus;
}
	
bool THTask::haveTaskName() {
	return (!_taskName.empty());
}

bool THTask::haveStartingDate() {
	return (!_StartingDate.empty());
}

bool THTask::haveStartingTime() {
	return (!_StartingTime.empty());
}

bool THTask::haveEndingDate() {
	return (!_EndingDate.empty());
}

bool THTask::haveEndingTime() {
	return (!_EndingTime.empty());
}

string THTask::getTaskName() {
	return _taskName;
}

string THTask::getStartingDate() {
	return _StartingDate;
}

string THTask::getStartingTime() {
	return _StartingTime;
}

string THTask::getEndingDate() {
	return _EndingDate;
}

string THTask::getEndingTime() {
	return _EndingTime;
}

bool THTask::getStatus() {
	return _isDone;
}

bool THTask::checkOverdue() {
	refresh();
	return _isOverdue;
}

bool THTask::checkToday() {
	refresh();
	return _isToday;
}

THUtility::TaskType THTask::getTaskType() {
	refresh();
	return _taskType;
}

//refresh is used to update _taskType, _isOverdue and _isToday which are determined by other date and time fields
//these three attributes are not set by users, but only updated with private methods
void THTask::refresh() {
	updateTaskType();

	if(_taskType == THUtility::TIMED) {
		rearrangeDateTime();
	}

	if(_taskType != THUtility::FLOATING) {
		_isOverdue = _taskTime.isOverdue(_StartingDate, _StartingTime);
		_isToday = _taskTime.isToday(_StartingDate);
	}
}

//update _taskType attribute of a THTask object, depEnding on the date and time attributes it have
//i.e. a THTask object without a Start date and an End date will be classified as a FLOATING task
void THTask::updateTaskType() {
	if(!haveStartingDate() && !haveStartingTime() && !haveEndingDate() && !haveEndingTime()) {
		_taskType = THUtility:: FLOATING;
	}

	if(haveStartingDate() && !haveEndingDate()) {
		_taskType = THUtility:: DEADLINE;   //we store the deadline date in _StartingDate, deadline time in _StartingTime
	}

	if(haveStartingDate() && haveEndingDate()) {
		_taskType = THUtility:: TIMED;
	}
}

//make sure that the End date of a TIMED task is always later than its Start date
//if a TIMED task Starts and Ends on the same day, the End time should always be later than the Start time
void THTask::rearrangeDateTime() {
	int StartingDateInt = stringToInt(_StartingDate);
	int EndingDateInt = stringToInt(_EndingDate);

	if(StartingDateInt > EndingDateInt) {
		string temp;
		
		temp       = _StartingDate;
		_StartingDate = _EndingDate;
		_EndingDate   = temp;

		if(!_EndingTime.empty()) {
			temp       = _StartingTime;
			_StartingTime = _EndingTime;
			_EndingTime   = temp;
		}
	} 
	
	if(StartingDateInt == EndingDateInt) {
		int StartingTimeInt = stringToInt(_StartingTime);
		int EndingTimeInt   = stringToInt(_EndingTime);

		if(StartingTimeInt > EndingTimeInt) {
			string temp;
		
			temp       = _StartingTime;
			_StartingTime = _EndingTime;
			_EndingTime   = temp;
		}
	}

	StartingDateInt = stringToInt(_StartingDate);
	EndingDateInt   = stringToInt(_EndingDate);

	assert(StartingDateInt <= EndingDateInt);  //_StartingDate must be earlier or equal to _EndingDate after this rearrange method
}

int THTask::stringToInt(string inputString) {
	return atoi(inputString.c_str());
}