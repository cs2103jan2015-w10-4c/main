
#include "UI.h"

const string UI::MESSAGE_WELCOME = "Welcome to Taskhub";

string UI::displayWelcomeMessage() {
	storage::programmeInitialising();
	Logic::getStorage();

	return MESSAGE_WELCOME;
}

void UI::showToUser(string text) {
	cout << text << endl;
}

string UI::getUserCommand() {
	string userCommand;

	cout << "command: ";
	getline(cin, userCommand);

	return userCommand;
}
