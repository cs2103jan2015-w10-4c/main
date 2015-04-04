
#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";
const string SCHEDULED_Task_LABEL = "timed";
const string DEADLINE_Task_LABEL = "deadline";
const string FLOATING_Task_LABEL = "floating";
const string PROCESSING_Task_LABEL = "progressing";
const string FINISHED_Task_LABEL = "done";
const string EMPTY_SPACE =" ";

string UI::displayWelcomeMessage() {
	StorageController::programmeInitialising();
	Logic::getStorage();

	return MESSAGE_WELCOME;
}

void UI::showToUser(string userCommand) {
	string command = Logic::getFirstWord(userCommand);
	string message = Logic::removeFirstWord(userCommand);
	
	if(command=="show"){
		vector<string> task = ShowDailyTask::messageDisplayed;
		
		if(message!="today")
			UI::dispalyDay(task,message);
		else
			UI::dispalyDay(task,"Today");
	}
	else if(command=="display"){
		vector<string> task = CommandDisplay::messageDisplayed;
		UI::dispalyDay(task,"Display");
	}
	else if(command=="sort"){
		vector<string> task = CommandDisplay::messageDisplayed;
		UI::dispalyDay(task,userCommand);
	}
	else if(command=="search"){
	
	}
	else{
		vector<string> task = ShowDailyTask::messageDisplayed;
		UI::dispalyDay(task, "Today");
	}

}
void UI::dispalyDay(vector<string> task, string heading){
	vector<Task> temporary;
	int indexAndNameLength=30;
	int dateLength=8;
	int timeLength=15;
	int venueLength=10;
	int statusLength=10;
	string date;
	string time;
	
	for(unsigned int i=0; i<task.size(); i++){
		Task temp(task[i]);
		temporary.push_back(temp);
	}

	HANDLE  hConsole;
			int k=9;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, k);
	cout << heading << " -----------------------------------------------------------" << endl;
	
	for(unsigned int i=0; i<temporary.size();i++){
		if(temporary[i].getStatus()==FINISHED_Task_LABEL){
			SetConsoleTextAttribute(hConsole, 10);
		}
		else SetConsoleTextAttribute(hConsole, 7);

		//check date
		if(temporary[i].getTaskType()==DEADLINE_Task_LABEL){
			date = "due "+ temporary[i].getDeadlineDate();
		}
		if(temporary[i].getTaskType()==SCHEDULED_Task_LABEL){
			date = temporary[i].getScheduledDate();
		}
		if(temporary[i].getTaskType()==FLOATING_Task_LABEL){
			date = EMPTY_SPACE;
		}
		//check time
		if(temporary[i].getTaskType()==DEADLINE_Task_LABEL){
			time = temporary[i].getDeadlineTime();
		}
		if(temporary[i].getTaskType()==SCHEDULED_Task_LABEL){
			time = temporary[i].getStartTime()+" - " + temporary[i].getEndTime();
		}
		if(temporary[i].getTaskType()==FLOATING_Task_LABEL){
			time = EMPTY_SPACE;
		}
		cout << left << setw(indexAndNameLength) << temporary[i].getTaskName() 
			<< setw(dateLength) << date
			<< setw(timeLength) << time
			<< setw(venueLength) << temporary[i].getVenue()
			<< setw(statusLength) << temporary[i].getStatus()
			<< endl;
	}
}
void UI::systemFeedback(string text){
	cout << text << endl;
}

string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);

	return userCommand;
}
