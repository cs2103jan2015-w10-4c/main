#include "Textbuddy.h"
#include <string>
using namespace std;

const string TextBuddy::MESSAGE_ERROR_DETECTED = "Expected: textbuddy.exe <fileName.txt>";
const string TextBuddy::MESSAGE_PROGRAMME_TERMINATED = "Press any key to exit...";
const string TextBuddy::MESSAGE_WELCOME = "Welcome to Textbuddy++. %s is ready for use";
const string TextBuddy::MESSAGE_WRONG_COMMAND = "Error: Wrong Command";
const string TextBuddy::MESSAGE_EMPTY = "%s is empty";
const string TextBuddy::MESSAGE_ADDED = "Added to %s: \"%s\"";
const string TextBuddy::MESSAGE_DELETED = "Deleted from %s: \"%s\"";
const string TextBuddy::MESSAGE_CLEARED = "All message is deleted from %s";
const string TextBuddy::MESSAGE_SORTED= "all messages in %s are sorted alphabetically";
const string TextBuddy::MESSAGE_CAN_FIND = "message is found at %d in %s";
const string TextBuddy::MESSAGE_CANNOT_FIND = "message cannot be found in %s";
const string TextBuddy::MESSAGE_PROMPT_COMMAND = "command: ";
const string TextBuddy::MESSAGE_WRONG_FORMAT = "wrong command format %s\n1. add <text>\n2. delete <line number>\n3. clear\n4. display\n5. sort\n6. search <word(s)>\n7. exit\n";

char TextBuddy::buffer[MAX_BUFERING_CAPACITY] = "";
vector<string> TextBuddy::storage;

int main(int argc, char* argv[]) {
	
	TextBuddy::main(argc, argv);
}

void TextBuddy::main(int argc, char* argv[]) {
	
	checkCommandLineInput(argc);
	initialStorage(argv[TEXT_FILE_NAME]);

	sprintf_s(buffer, MESSAGE_WELCOME.c_str(), argv[TEXT_FILE_NAME]);
	showToUser(buffer);
	getUserInput(argv[TEXT_FILE_NAME]);

	return;
}

void TextBuddy::checkCommandLineInput(int argc) {
	
	if (argc != CORRECT_ARGUMENT) {
		showToUser(MESSAGE_ERROR_DETECTED);
		showToUser(MESSAGE_PROGRAMME_TERMINATED);

		getchar();
		exit(0);
	}
}

void TextBuddy::getUserInput(string fileName) {
	
	while (true) {

		string userCommand=getUserCommand();
		string feedback = executeCommand(fileName, userCommand);

		writeToFile(fileName);
		showToUser(feedback);
	}

	return;
}

string TextBuddy::getUserCommand() {

	cout << MESSAGE_PROMPT_COMMAND;
	
	string userCommand;
	getline(cin, userCommand);

	return userCommand;
}

void TextBuddy::showToUser(string text) {

	cout<< text << endl;
}


// checks if user input is invalid
bool TextBuddy::isValidInput(string message) {
	if (message == "" || message == " ") {
		return false;
	}
	return true;
}

// this function is to get the message if the input is valid
string TextBuddy::removeFirstWord(string command) {
	
	if (command.find_first_of(" ") == string::npos) {
		return "";
	}
	return command.substr(command.find_first_of(" ") + 1);
}


// this function is to get the command
string TextBuddy::getFirstWord(string command) {
	
	return command.substr(0, command. find(' '));
}

// parse the command and pass it to correct operation
string TextBuddy::executeCommand(string fileName, string userCommand) {
	
	CommandType command;
	string message;

	command = determineCommandType(getFirstWord(userCommand));
	message = removeFirstWord(userCommand);


	switch (command) {
	case ADD_LINE:
		if (!isValidInput(message)) {
			sprintf_s(buffer, MESSAGE_WRONG_FORMAT.c_str(), getFirstWord(userCommand).c_str());
			return buffer;
		}
		return addLine(fileName, message);

	case DISPLAY_ALL:
		return displayAll(fileName);

	case DELETE_LINE:
		if (!isValidInput(message)) {
			sprintf_s(buffer, MESSAGE_WRONG_FORMAT.c_str(), command);
			return buffer;
		}
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

// determine the command type of input 
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


string TextBuddy::addLine(string fileName, string message) {

	storage.push_back(message);

	sprintf_s(buffer, MESSAGE_ADDED.c_str(), fileName.c_str(), message.c_str());

	return buffer;
}

string TextBuddy::clearAll(string fileName) {

	storage.clear();

	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), fileName.c_str());

	return buffer;
}

string TextBuddy::deleteLine(string fileName, string message) {

	vector<string>::iterator i = getLineIterator(fileName, message);

	sprintf_s(buffer, MESSAGE_DELETED.c_str(), fileName.c_str(), i->c_str());

	storage.erase(i);

	return buffer;
}

// displays all message in the text file
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

// sort the lines in alphabetical order
string TextBuddy::sortLineAlphabetically(string fileName) {
	stable_sort(storage.begin(), storage.end());

	sprintf_s(buffer, MESSAGE_SORTED.c_str(), fileName.c_str());

	return buffer;
}

// searches the textfile for search word/phrase
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

// returns message of line number if search word is found
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

// returns iterator of line number requested (1 <= line number <= n)
vector<string>::iterator TextBuddy::getLineIterator(string fileName, string message) {
	
	int i = 1;

	for (vector<string>::iterator iter = storage.begin(); iter != storage.end(); iter++) {
		if (i == stoi(message)) {
			return iter;
		}
		else
			i++;
	}

	sprintf_s(buffer, MESSAGE_CANNOT_FIND.c_str(), fileName.c_str());

	showToUser(buffer);

	return storage.end();
}

// transfers strings in vector to file (1 string in vector = 1 line in file)
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

// outputs string with line number 
void TextBuddy::printLine(int i, string line) {
	
	cout << i << ". " << line << endl;
}

// initialises the vector and *.txt 
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
