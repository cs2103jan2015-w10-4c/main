#include "UI.h"
#include "CommandInterpreter.h"
#include <stdlib.h>
#include <Windows.h>

int main() {
	

	UI::programmeInitialising();
	UI::displayWelcomeMessage();
//cout << "\n============================================================================" << endl;
	UI::showToUser("show today");
	while (true) {

		
		string userCommand = UI::getUserCommand();
		cout << endl;
		string output = CommandInterpreter::executeUserCommand(userCommand);
		UI::displayWelcomeMessage();
		UI::showToUser(userCommand);
		cout << endl<< endl<< endl;
		UI::systemFeedback(output);
		cout << "\n=============================================================================="<<endl;;
	}

	return 0;
}