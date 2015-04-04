#include <stdlib.h>
#include "..\TaskHub\UI.h"
#include "..\TaskHub\CommandInterpreter.h"


int main() {
	/*UI::showToUser(UI::displayWelcomeMessage());
	cout << "==========================================" << endl;
	while (true) {

		
		string userCommand = UI::getUserCommand();
		string output = CommandInterpreter::executeUserCommand(userCommand);
		UI::showToUser(output);
		cout << "\n====================================" << endl;;
	}

	//	system("pause");*/

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