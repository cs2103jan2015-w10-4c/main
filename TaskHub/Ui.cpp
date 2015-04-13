#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";
const string SCHEDULED_Task_LABEL = "timed";
const string DEADLINE_Task_LABEL = "deadline";
const string FLOATING_Task_LABEL = "floating";
const string PROCESSING_Task_LABEL = "progressing";
const string FINISHED_Task_LABEL = "done";
const string UNCOMPLETED_TASK_LABLE = "uncompleted";
const string EMPTY_SPACE_DOUBLE ="  ";
const string DUMMY_INPUT_FOR_SECOND_TASK_CONSTRUCTOR = "00";
const string COMMAND_TYPE_SHOW = "show";
const string COMMAND_TYPE_DISPLAY = "display";
const string COMMAND_TYPE_SORT = "sort";
const string COMMAND_TYPE_SEARCH = "search";
const string COMMAND_TYPE_DETAIL = "detail";
const string COMMAND_MESSAGE_TODAY = "today";
const string COMMAND_MESSAGE_FREE = "free";
const int COLOR_FINISHED_TASK = 250;
const int COLOR_UNCOMPLETED_TASK = 249;
const int COLOR_NORAL_BACKGROUND = 243;
const int COLOR_WELCOME_MESSAGE = 244;
const int LENGTH_INDEX_AND_TASK_NAME=18;
const int LENGTH_DATE=10;
const int LENGTH_TIME=15;
const int LENGTH_VENUE=13;
const int LENGTH_STATUS=12;
const int LENGTH_DOUBLE_EMPTY_SPACE = 2;
const int LENGTH_LEFT_SIDE_FORMAT = 4;
const int LENGTH_RIGHT_SIDE_FORMAT = 8;
const int START_OF_A_STRING = 0;

void UI::programmeInitialising() {
	StorageController::programmeInitialising();
	Logic::getStorage();
}

void UI::displayWelcomeMessage() {
	HANDLE  hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, COLOR_WELCOME_MESSAGE);

	cout    <<"\n                              WELCOME TO TASKHUB ^-^                          "
			<<"\n INPUT FORMAT:   "
			<<"\n	Scheduled Task: add meeting -from 13:00 -to 14:00 11/12 @utown  "
			<<"\n	Deadline Task: add meeting -by 13:00 11/12 @utown   "
			<<"\n	Floating Task: add meeting   "
			<<"\n	Recurring Task: recurring meeting 11/12 08:00 09:00 -every mon   "
			<<"\n ******************************************************************************      "
			<<endl<<endl;

	SetConsoleTextAttribute(hConsole,COLOR_NORAL_BACKGROUND);
}

void UI::showToUser(string userCommand) {
	string command = Logic::getFirstWord(userCommand);
	string message = Logic::removeFirstWord(userCommand);

	if(command==COMMAND_TYPE_SHOW){
		string aa= ShowDailyTask::showDayTask(message);
		vector<string> task = ShowDailyTask::messageDisplayed;
		size_t free = message.find(COMMAND_MESSAGE_FREE);

		if(message==COMMAND_MESSAGE_TODAY) {
			UI::displayDay(task,COMMAND_MESSAGE_TODAY);
		}
		else if(free!=string::npos) {
			UI::displayDay(task, message);
		}
		else {
			UI::displayDay(task,message);
		}
	}
	else if(command==COMMAND_TYPE_DISPLAY) {
		vector<string> task = CommandDisplay::messageDisplayed;
		UI::displayDay(task,COMMAND_TYPE_DISPLAY);
	}
	else if(command==COMMAND_TYPE_SORT) {
		vector<string> task = CommandDisplay::messageDisplayed;
		UI::displayDay(task,userCommand);
	}
	else if(command==COMMAND_TYPE_SEARCH) {
		string temp= CommandSearch::searchMessage(message);
		vector<string> task = CommandSearch::messageDisplayed;
		UI::displayDay(task,userCommand);
	}
	else if(command==COMMAND_TYPE_DETAIL) {
		string task = CommandDetail::detailMessage(message);
		if(!task.empty()) {
		UI::displayDetail(task,message);
		}
	}
	else {
		string temp= ShowDailyTask::showDayTask(COMMAND_MESSAGE_TODAY);
		vector<string> task = ShowDailyTask::messageDisplayed;
		UI::displayDay(task, COMMAND_MESSAGE_TODAY);
	}
	cout << "\n -----------------------------------------------------------------------------" 
		 << endl;
}

void UI::displayDetail(string task, string index) {
	Task temp(task,DUMMY_INPUT_FOR_SECOND_TASK_CONSTRUCTOR);

	cout << "\n Detail of task " << index << " :";
	cout <<"\n -----------------------------------------------------------------------------";
	cout << "\n [TASK NAME]: " << temp.getTaskName();
	if(temp.getTaskType()==SCHEDULED_Task_LABEL){
		cout << "\n [DATE]: " << temp.getScheduledDate()
			 << "\n [TIME]: " << temp.getStartTime() << " - " << temp.getEndTime();
	}
	else if(temp.getTaskType()==DEADLINE_Task_LABEL){
		cout << "\n [DEADLINE]: " << temp.getDeadlineDate() << EMPTY_SPACE_DOUBLE << temp.getDeadlineTime();
	}
	cout << "\n [VENUE]: " << temp.getVenue()
		 << "\n [STATUS]: " << temp.getStatus();
}

void UI::displayDay(vector<string> task, string heading) {
	vector<Task> temporary;
	string date;
	string time;
	size_t free = heading.find(COMMAND_MESSAGE_FREE);
	size_t search = heading.find(COMMAND_TYPE_SEARCH);
	HANDLE  hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	heading[START_OF_A_STRING]=toupper(heading[START_OF_A_STRING]);
	cout << heading << " :";
	cout <<"\n -----------------------------------------------------------------------------";

	if(task.empty()) {
		assert(!task.empty());
		if(search!=string::npos) {
			cout << "\n                         SORRY NOTHING IS FOUND T_T                            " << endl;
		}
		else {
			cout << "\n                              YAY! YOU ARE FREE! ^-^                           " ;
		}
	}
	else {
		for(unsigned int i=0; i<task.size(); i++) {
			Task temp(task[i],DUMMY_INPUT_FOR_SECOND_TASK_CONSTRUCTOR);
			temporary.push_back(temp);
	    }
		if(free!=string::npos) {
			for(unsigned int i=0;i<task.size();i++) {
				cout << task[i] << endl;
			}
		}
		else {
			for(unsigned int i=0; i<temporary.size();i++) {
				cout<< left << setw(LENGTH_LEFT_SIDE_FORMAT) <<"\n|";
				if(temporary[i].getStatus()==FINISHED_Task_LABEL) {
					SetConsoleTextAttribute(hConsole,COLOR_FINISHED_TASK);
				}
				else {
					SetConsoleTextAttribute(hConsole, COLOR_NORAL_BACKGROUND);
				}
				if(temporary[i].getStatus()==UNCOMPLETED_TASK_LABLE) {
					SetConsoleTextAttribute(hConsole,COLOR_UNCOMPLETED_TASK);
				}
				else {
					SetConsoleTextAttribute(hConsole, COLOR_NORAL_BACKGROUND);
				}
				//check date
				if(temporary[i].getTaskType()==DEADLINE_Task_LABEL) {
					date = "due "+ temporary[i].getDeadlineDate();
				}
				if(temporary[i].getTaskType()==SCHEDULED_Task_LABEL) {
					date = temporary[i].getScheduledDate();
				}
				if(temporary[i].getTaskType()==FLOATING_Task_LABEL) {
					date = EMPTY_SPACE_DOUBLE;
				}
				//check time
				if(temporary[i].getTaskType()==DEADLINE_Task_LABEL) {
					time = temporary[i].getDeadlineTime();
				}
				if(temporary[i].getTaskType()==SCHEDULED_Task_LABEL) {
					time = temporary[i].getStartTime()+" - " + temporary[i].getEndTime();
				}
				if(temporary[i].getTaskType()==FLOATING_Task_LABEL) {
					time = EMPTY_SPACE_DOUBLE;
				}
				cout<< left << setw(LENGTH_INDEX_AND_TASK_NAME) << temporary[i].getTaskName().substr(START_OF_A_STRING,LENGTH_INDEX_AND_TASK_NAME-LENGTH_DOUBLE_EMPTY_SPACE) 
					<< setw(LENGTH_DATE) << date.substr(START_OF_A_STRING,LENGTH_DATE)
					<< setw(LENGTH_TIME) << time.substr(START_OF_A_STRING,LENGTH_TIME)
					<< setw(LENGTH_VENUE) << temporary[i].getVenue().substr(START_OF_A_STRING,LENGTH_VENUE)
					<< setw(LENGTH_STATUS) << temporary[i].getStatus().substr(START_OF_A_STRING,LENGTH_STATUS);
				SetConsoleTextAttribute(hConsole, COLOR_NORAL_BACKGROUND);
				cout << right << setw(LENGTH_RIGHT_SIDE_FORMAT)<<"|";
			}
		}
	}
}

void UI::systemFeedback(string text) {
	cout << text;
}

string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);
	system("CLS");
	return userCommand;
}
