
#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";
const string SCHEDULED_Task_LABEL = "timed";
const string DEADLINE_Task_LABEL = "deadline";
const string FLOATING_Task_LABEL = "floating";
const string PROCESSING_Task_LABEL = "progressing";
const string FINISHED_Task_LABEL = "done";
const string EMPTY_SPACE =" ";
const int FINISHED_TASK_COLOR = 250;
const int NORAL_BACKGROUND_COLOR = 243;
const int WELCOME_MESSAGE_COLOR = 244;

void UI::programmeInitialising() {
	StorageController::programmeInitialising();
	Logic::getStorage();
}

void UI::displayWelcomeMessage(){
	HANDLE  hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, WELCOME_MESSAGE_COLOR);

	cout     <<"\n                              WELCOME TO TASKHUB ^-^                          "
			 <<"\n ******************************************************************************      "
			 <<endl<<endl;
	SetConsoleTextAttribute(hConsole, NORAL_BACKGROUND_COLOR);

}

void UI::showToUser(string userCommand) {
	string command = Logic::getFirstWord(userCommand);
	string message = Logic::removeFirstWord(userCommand);

	
	
	if(command=="show"){
		string aa= ShowDailyTask::showDayTask(message);
		vector<string> task = ShowDailyTask::messageDisplayed;
		size_t free = message.find("free");

		if(message=="today")
			UI::dispalyDay(task,"Today");
		else if(free!=string::npos){
			
			UI::dispalyDay(task, message);
		}
		else{
			UI::dispalyDay(task,message);
		}
		
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
		string temp= CommandSearch::searchMessage(message);
		vector<string> task = CommandSearch::messageDisplayed;
		//cout << task[0]<<endl;
		UI::dispalyDay(task,userCommand);
	}
	else if(command=="detail"){
		
	}
	else{
		string temp= ShowDailyTask::showDayTask("today");
		vector<string> task = ShowDailyTask::messageDisplayed;
		//cout << task[0]<<endl;
		UI::dispalyDay(task, "Today");
		
	}
	cout << "\n -----------------------------------------------------------------------------" 
			<< endl;

}
void UI::dispalyDay(vector<string> task, string heading){
	vector<Task> temporary;
	int indexAndNameLength=20;
	int dateLength=8;
	int timeLength=15;
	int venueLength=13;
	int statusLength=12;
	string date;
	string time;
	size_t free = heading.find("free");
	size_t search = heading.find("search");
	
	

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << heading << " :";
	cout <<"\n -----------------------------------------------------------------------------";

	if(task.empty()){
		if(search!=string::npos){
			cout << "\n                         SORRY NOTHING IS FOUND T_T                            " << endl;
		}
		else{
			cout << "\n                              YAY! YOU ARE FREE! ^-^                           " ;
		}
	}
	else{
		for(unsigned int i=0; i<task.size(); i++){
		Task temp(task[i],"input");
		temporary.push_back(temp);
	    }

		if(free!=string::npos){
			for(unsigned int i=0;i<task.size();i++){
					cout << task[i] << endl;
			}
		}
		else{
			for(unsigned int i=0; i<temporary.size();i++){
				cout<< left << setw(4) <<"\n|";
				if(temporary[i].getStatus()==FINISHED_Task_LABEL){
					SetConsoleTextAttribute(hConsole, FINISHED_TASK_COLOR);
				}
				else SetConsoleTextAttribute(hConsole, NORAL_BACKGROUND_COLOR);

				//check date
				if(temporary[i].getTaskType()==DEADLINE_Task_LABEL){
					date = "due "+ temporary[i].getDeadlineDate();
				}
				if(temporary[i].getTaskType()==SCHEDULED_Task_LABEL){
					date = temporary[i].getScheduledStartDate();
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
				cout<< left << setw(indexAndNameLength) << temporary[i].getTaskName().substr(0,indexAndNameLength-2) 
					<< setw(dateLength) << date.substr(0,dateLength)
					<< setw(timeLength) << time.substr(0,timeLength)
					<< setw(venueLength) << temporary[i].getVenue().substr(0,venueLength)
					<< setw(statusLength) << temporary[i].getStatus().substr(0,statusLength);
			

			
			SetConsoleTextAttribute(hConsole, NORAL_BACKGROUND_COLOR);
			cout << right << setw(8)<<"|";
			}
		}
	}
}
void UI::systemFeedback(string text){
	cout << text ;
}

string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);
	system("CLS");
	return userCommand;
}
