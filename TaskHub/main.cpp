#include "UI.h"
#include "Parser.h"
#include "storage.h"
#include "Logic.h"

int main() {
	UI::showToUser(UI::displayWelcomeMessage());
	cout << "=========================================="<<endl;
	while (true) {

		string userCommand = UI::getUserCommand();
		string output = UI::executeUserCommand(userCommand);
		UI::showToUser(output);
		cout << "\n===================================="<<endl;;
    }

//	system("pause");
	return 0;
}