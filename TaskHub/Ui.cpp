
#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";

string UI::displayWelcomeMessage() {
	StorageController::programmeInitialising();
	Logic::getStorage();

	return MESSAGE_WELCOME;
}

void UI::showToUser(string text) {
	cout << text << endl;
}
//testing 
string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);

	return userCommand;
}
