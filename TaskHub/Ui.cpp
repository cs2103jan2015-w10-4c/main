
#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";

string UI::displayWelcomeMessage() {
	StorageController::programmeInitialising();
	Logic::getStorage();

	return MESSAGE_WELCOME;
}

void UI::showToUser(string userCommand, string text) {
	size_t _command = userCommand.find_first_of(" ");
	string command = userCommand.substr(0,_command);
	string message = userCommand.substr(_command+1);
	
	if(command=="show"){
		if(message=="today"){
			cout << ShowDailyTask::showDayTask("today") << endl<<endl<<endl<<endl;
		}
		else{
			cout << ShowDailyTask::showDayTask(message) << endl<<endl<<endl<<endl;
		}
	}
	else{
		cout << ShowDailyTask::showDayTask("today") << endl<<endl<<endl<<endl;
	}
	cout << text << endl;
}

string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);

	return userCommand;
}
