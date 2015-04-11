
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include "..\TaskHub\Ui.h"
#include "..\TaskHub\CommandInterpreter.h"

//const int FINISHED_TASK_COLOR = 250;
const int NORAL_BACKGROUND_COLOR = 243;
const int WELCOME_MESSAGE_COLOR = 244;
const int SYSTEM_FEEDBACK_COLOR = 252;

int main() {
	UI::programmeInitialising();
	string temp;
	getline(cin,temp);
	system("CLS");
	UI::displayWelcomeMessage();

	//cout << "\n============================================================================" << endl;
	
	UI::showToUser("show today");
	
	while (true) {

		string userCommand = UI::getUserCommand();

		cout << endl;

		string output = CommandInterpreter::executeUserCommand(userCommand);

		UI::displayWelcomeMessage();
		UI::showToUser(userCommand);

		cout << endl << endl << endl;
		HANDLE  hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, SYSTEM_FEEDBACK_COLOR);

		UI::systemFeedback(output);
		SetConsoleTextAttribute(hConsole, NORAL_BACKGROUND_COLOR);

		cout << "\n==============================================================================" << endl;;
	}

	return 0;
}