#include "StorageController.h"

vector<string> StorageController::Task;
const string StorageController::fileName = "storage.txt";

void StorageController::programmeTerminating() {
	ofstream file;
	string currentLine;

	remove(fileName.c_str());

	file.open(fileName);
	currentLine = Logic::display();
	file << currentLine << endl;	
	file.close();
}

void StorageController::programmeInitialising() {
	ifstream file;
	string currentLine;

	Task.clear();
	file.open(fileName);

	while(getline(file,currentLine)) {
		Task.push_back(currentLine);
	}
	file.close();
}

vector<string> StorageController::returnTask() {
	return Task;
}
