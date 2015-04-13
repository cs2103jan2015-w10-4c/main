//@author A0115793Y
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include "..\TaskHub\Ui.h"
#include "..\TaskHub\CommandInterpreter.h"
#include "..\TaskHub\StorageController.h"

const int COLOR_NORAL_BACKGROUND = 243;
const int COLOR_WELCOME_MESSAGE = 244;
const int COLOR_SYSTEM_FEEDBACK = 252;

int main() {
	
	UI::programmeInitialising();
	//get dummay input because of user file prompt 
	string temp;
	getline(cin,temp);
	
	system("CLS");
	
	//display to user
	UI::displayWelcomeMessage();
	UI::showToUser("show today");
	
	while (true) {
		string userCommand = UI::getUserCommand();

		//logging
		StorageController::taskLog->updateTaskLog(userCommand);

		//execute user command
		cout << endl;
		string output = CommandInterpreter::executeUserCommand(userCommand);
		
		//display to user
		UI::displayWelcomeMessage();
		UI::showToUser(userCommand);
		cout << endl << endl << endl;

		//change color to show system feedback 
		HANDLE  hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, COLOR_SYSTEM_FEEDBACK);
		UI::systemFeedback(output);
		SetConsoleTextAttribute(hConsole, COLOR_NORAL_BACKGROUND);
		cout << "\n==============================================================================" << endl;;
	}
	return 0;
}