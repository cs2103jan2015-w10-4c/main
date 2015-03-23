#include "storage.h"

vector<string> storage::Task;
const string storage::fileName = "storage.txt";

void storage::programmeTerminating() {
	ofstream file;
	string currentLine;

	remove(fileName.c_str());

	file.open(fileName);
	currentLine = Logic::display();
	file << currentLine << endl;	
	file.close();
}

void storage::programmeInitialising() {
	ifstream file;
	string currentLine;

	Task.clear();
	file.open(fileName);

	while(getline(file,currentLine)) {
		Task.push_back(currentLine);
	}
	file.close();
}

vector<string> storage::returnTask() {
	return Task;
}
