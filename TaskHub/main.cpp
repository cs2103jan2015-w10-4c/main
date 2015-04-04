#include "UI.h"
#include "CommandInterpreter.h"
#include <stdlib.h>

int main() {
	/*
	while (true) {

		//system("CLS");
		UI::showToUser("xx",UI::displayWelcomeMessage());
		cout << "=========================================="<<endl;
		string userCommand = UI::getUserCommand();
		string output = CommandInterpreter::executeUserCommand(userCommand);
		UI::showToUser(userCommand,output);
		cout << "\n===================================="<<endl;;
    }

//	system("pause");
*/
		cout<< UI::displayWelcomeMessage()<< endl;
		cout << "=========================================="<<endl;
		cout << ShowDailyTask::showDayTask("today")<<endl;
		string userCommand = UI::getUserCommand();
		system("CLS");
		while(!userCommand.empty()){

			string output = CommandInterpreter::executeUserCommand(userCommand);
			UI::showToUser(userCommand,output);
			cout << "\n===================================="<<endl;;
			userCommand = UI::getUserCommand();
			system("CLS");
			cout<< UI::displayWelcomeMessage() << endl;
			cout << "=========================================="<<endl;
		}
	return 0;
}