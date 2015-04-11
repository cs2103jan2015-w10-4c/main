
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include "..\TaskHub\Ui.h"
#include "..\TaskHub\CommandInterpreter.h"

const int COLOR_NORAL_BACKGROUND = 243;
const int COLOR_WELCOME_MESSAGE = 244;
const int COLOR_SYSTEM_FEEDBACK = 252;

int main() {
	UI::programmeInitialising();
	
	string temp;
	getline(cin,temp);
	
	system("CLS");
	UI::displayWelcomeMessage();
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
		SetConsoleTextAttribute(hConsole, COLOR_SYSTEM_FEEDBACK);
		UI::systemFeedback(output);
		SetConsoleTextAttribute(hConsole, COLOR_NORAL_BACKGROUND);
		cout << "\n==============================================================================" << endl;;
	}
	return 0;
}