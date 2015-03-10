// Student: Liao Dianze
// Matriculation Card: A0115365J
// Tutorial Group: w10

// Please delete after this: push testing - Shi Xuan**

#include "Textbuddy.h"
using namespace std;

const string TextBuddy::MESSAGE_ERROR_DETECTED = "Expected: textbuddy.exe <fileName.txt>";
const string TextBuddy::MESSAGE_PROGRAMME_TERMINATED = "Press any key to exit...";
const string TextBuddy::MESSAGE_WELCOME = "Welcome to Textbuddy++. %s is ready for use";
const string TextBuddy::MESSAGE_WRONG_COMMAND = "Error: Wrong Command";
const string TextBuddy::MESSAGE_EMPTY = "%s is empty";
const string TextBuddy::MESSAGE_ADDED = "Added to %s: \"%s\"";
const string TextBuddy::MESSAGE_DELETED = "Deleted from %s: \"%s\"";
const string TextBuddy::MESSAGE_CLEARED = "All messages are deleted from %s";
const string TextBuddy::MESSAGE_SORTED = "All messages in %s are sorted alphabetically";
const string TextBuddy::MESSAGE_SORTING_ERROR = "The file is empty and cannot be sorted"; 
const string TextBuddy::MESSAGE_CAN_FIND = "Message is found at %d in %s";
const string TextBuddy::MESSAGE_CANNOT_FIND = "Message cannot be found in %s";
const string TextBuddy::MESSAGE_PROMPT_COMMAND = "command: ";
const string TextBuddy::MESSAGE_WRONG_FORMAT = "Wrong command format %s\n1. add <text>\n2. delete <line number>\n3. clear\n4. display\n5. sort\n6. search <word(s)>\n7. exit\n";

// to make up the correct messages to be displayed to user
char TextBuddy::buffer[MAX_BUFERING_CAPACITY] = "";
vector<string> TextBuddy::storage;

// redirect to the user-defined main function for the ease of implementation
int main(int argc, char* argv[]) {
	
	TextBuddy::main(argc, argv);
}

// user-defined main function
void TextBuddy::main(int argc, char* argv[]) {
	
	checkCommandLineInput(argc);
	initialStorage(argv[TEXT_FILE_NAME]);

	// this is to display welcome message with the filename created
	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[TEXT_FILE_NAME]);
	showToUser(buffer);

	getUserInput(argv[TEXT_FILE_NAME]);

	return;
}

// check the corectness of the initial command line input, i.e., should have appname.exe and filename.txt
void TextBuddy::checkCommandLineInput(int argc) {
	
	if (argc != CORRECT_ARGUMENT) {
		showToUser(MESSAGE_ERROR_DETECTED);
		showToUser(MESSAGE_PROGRAMME_TERMINATED);

		getchar();
		exit(0);
	}
}

// pass userCommand got to designated function
// and to show the requested feedback if execution is successful
void TextBuddy::getUserInput(string fileName) {
	
	while (true) {

		string userCommand = getUserCommand();
		string feedback = executeCommand(fileName, userCommand);

		writeToFile(fileName);
		showToUser(feedback);
	}

	return;
}

// this is to get user command
string TextBuddy::getUserCommand() {

	cout << MESSAGE_PROMPT_COMMAND;
	
	string userCommand;
	getline(cin, userCommand);

	return userCommand;
}

// to print out the desired text
void TextBuddy::showToUser(string text) {

	cout << text << endl;
}


// checks whether user input is valid
bool TextBuddy::isValidInput(string message) {
	if (message == "" || message == " ") {
		return false;
	}
	return true;
}

// to get the message only if the input is valid
string TextBuddy::removeFirstWord(string command) {
	
	if (command.find_first_of(" ") == string::npos) {
		return "";
	}
	return command.substr(command.find_first_of(" ") + 1);
}


// to get the user command
string TextBuddy::getFirstWord(string command) {
	
	return command.substr(0, command. find(' '));
}

// identify the command and the message
// and pass it to the correct function
string TextBuddy::executeCommand(string fileName, string userCommand) {
	
	CommandType command = determineCommandType(getFirstWord(userCommand));
	string message = removeFirstWord(userCommand);

	switch (command) {
	case ADD_LINE:
		return addLine(fileName, message);

	case DISPLAY_ALL:
		return displayAll(fileName);

	case DELETE_LINE:
		return deleteLine(fileName, message);

	case CLEAR_ALL:
		return clearAll(fileName);

	case SORT:
		return sortLineAlphabetically(fileName);

	case SEARCH: 
		return searchForWord(fileName, message);

	case EXIT:
		exit(0);

	case INVALID:
		sprintf_s(buffer, MESSAGE_WRONG_FORMAT.c_str(), userCommand.c_str());
		return buffer;

	default:
		showToUser(MESSAGE_WRONG_COMMAND);
		showToUser(MESSAGE_PROGRAMME_TERMINATED);

		getchar();
		exit(EXIT_FAILURE);
	}

}

// determine the command type 
TextBuddy::CommandType TextBuddy::determineCommandType(string userCommand) {
	
	transform(userCommand.begin(), userCommand.end(), userCommand.begin(), ::tolower);

	if (userCommand == "add") {
		return CommandType::ADD_LINE;

	}else if (userCommand == "display") {
		return CommandType::DISPLAY_ALL;

	}else if (userCommand == "clear") {
		return CommandType::CLEAR_ALL;

	}else if (userCommand == "delete") {
		return CommandType::DELETE_LINE;

	}else if (userCommand == "exit") {
		return CommandType::EXIT;

	}else if (userCommand== "sort") {
		return CommandType::SORT;

	}else if (userCommand== "search") {
		return CommandType::SEARCH;
	}else {
		return CommandType::INVALID;
	}
}

// to add a message
string TextBuddy::addLine(string fileName, string message) {
	string userCommand="add";

	//only add to the file if there is message after "add", i.e, to add "" or " " is impossible
	if (!isValidInput(message)) {
		sprintf_s(buffer, MESSAGE_WRONG_FORMAT.c_str(), getFirstWord(userCommand).c_str());
	} else {
	
	storage.push_back(message);
	sprintf_s(buffer, MESSAGE_ADDED.c_str(), fileName.c_str(), message.c_str());

	}
	return buffer;
}

// to clear all message
string TextBuddy::clearAll(string fileName) {

	storage.clear();

	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), fileName.c_str());

	return buffer;
}

// to delete unwanted message
string TextBuddy::deleteLine(string fileName, string message) {

	string command="delete";
	// can only delete message that is valid, i.e. to delete "" or " " is impossible
	if (!isValidInput(message)) {
		sprintf_s(buffer, MESSAGE_WRONG_FORMAT.c_str(), command);

	} else {
	vector<string>::iterator i = getLineIterator(fileName, message);
	sprintf_s(buffer, MESSAGE_DELETED.c_str(), fileName.c_str(), i->c_str());
	storage.erase(i);
	}

	return buffer;
}

// display all messages in the file
string TextBuddy::displayAll(string fileName) {

	int lineNumber = BEGINNING_LINE; 

	if (storage.begin() == storage.end()) {
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
		return buffer;
	}

	for (vector<string>::iterator iter = storage.begin(); iter != storage.end(); iter++) {
		printLine(lineNumber, *iter);
		lineNumber++;
	}

	return "";
}

// sort all the messages in alphabetical order
string TextBuddy::sortLineAlphabetically(string fileName) {
	
	if (!storage.empty()) {
	    stable_sort(storage.begin(), storage.end());
		sprintf_s(buffer, MESSAGE_SORTED.c_str(), fileName.c_str());

	} else {
		sprintf_s(buffer, MESSAGE_SORTING_ERROR.c_str(), fileName.c_str());	
	}

	return buffer;
}

// search the file for search word(s)
string TextBuddy::searchForWord(string fileName, string message) {
	int resultNumber = NOT_FOUND;

	for (int i = 1; i <= (int)storage.size(); i++) {

		string result = searchForLine(fileName, message, to_string(i));
		if (result != "") {
			resultNumber++;
			printLine(resultNumber, result);
		}
	}

	if (resultNumber == NOT_FOUND) {
		sprintf_s(buffer, MESSAGE_CANNOT_FIND.c_str(), fileName.c_str());
	} else {
		sprintf_s(buffer, MESSAGE_CAN_FIND.c_str(), resultNumber, fileName.c_str());
	}

	return buffer;
}

// search for the line number, and return if any, or an empty string if nothing is found
string TextBuddy::searchForLine(string fileName, string message, string lineNumber) {
	string::iterator lineChecker;

	vector<string>::iterator iter = getLineIterator(fileName, lineNumber);
	lineChecker = search(iter->begin(), iter->end(), message.begin(), message.end());

	if (iter->begin() == iter->end() || lineChecker == iter->end()) {
		return "";
	}
	else {
		return *iter;
	}
}

// return iterator of line number the searched word(s) is in
vector<string>::iterator TextBuddy::getLineIterator(string fileName, string message) {
	
	int i = 1;

	for (vector<string>::iterator iter = storage.begin(); iter != storage.end(); iter++) {
		if (i == stoi(message)) {
			return iter;
		}
		else {
			i++;
		}
	}

	sprintf_s(buffer, MESSAGE_CANNOT_FIND.c_str(), fileName.c_str());

	showToUser(buffer);

	return storage.end();
}

// transfer strings in vector to file (1 string in vector = 1 line in file)
void TextBuddy::writeToFile(string fileName) {
	
	ofstream file;

	file.open(fileName);
	file.close();

	if (storage.begin() != storage.end()) {
		for (vector<string>::iterator i = storage.begin(); i != storage.end(); i++) {
			file.open(fileName, ios::app);
			file << *i << endl;
			file.close();
		}
	}

	return;
}

// output string with line number for search purpose.
void TextBuddy::printLine(int i, string line) {
	
	cout << i << ". " << line << endl;
}

// initialise the vector and *.txt 
void TextBuddy::initialStorage(string fileName) {
	
	ifstream inFile;
	string line;

	inFile.open(fileName);

	while (getline(inFile, line)) {
		storage.push_back(line);
	}

	inFile.close();

	return;
}

//  only for test purpose, to check if 
string TextBuddy::checkCommandType(TextBuddy::CommandType command) {

	switch (command){
		case ADD_LINE:
			return "add";
		case DISPLAY_ALL:
			return "display";
		case DELETE_LINE:
			return "delete";
		case CLEAR_ALL:
			return "clear";
		case SORT:
			return "sort";
		case SEARCH:
			return "search";
		case EXIT:
			return "exit";
		case INVALID:
			return "invalid";
		default:
			return "error";
	}

}
