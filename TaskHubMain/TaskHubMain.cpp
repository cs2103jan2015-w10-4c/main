#include "..\TaskHub\UI.h"
#include "..\TaskHub\CommandInterpreter.h"

int main() {
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
}