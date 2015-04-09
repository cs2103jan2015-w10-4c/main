#include "..\TaskHub\UI.h"
#include "..\TaskHub\CommandInterpreter.h"

//#include "UI.h"
//#include "CommandInterpreter.h"
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



/*int main() {
	UI::showToUser(UI::displayWelcomeMessage());
	cout << "==========================================" << endl;
	while (true) {

		
		string userCommand = UI::getUserCommand();
		string output = CommandInterpreter::executeUserCommand(userCommand);
		UI::showToUser(output);
		cout << "\n====================================" << endl;;
	}

	//	system("pause");
	return 0;
}*/