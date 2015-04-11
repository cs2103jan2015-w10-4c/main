//@author A0111322E

#include "StorageController.h"

vector<string> StorageController::TaskList;
std::string StorageController::_fileName;
const std::string StorageController::_lastSaveFileName = "LastSaveFile.txt";

TaskLog* StorageController::taskLog;
StorageDatabase* StorageController::_databaseObj = new StorageDatabase();
StorageProcessor* StorageController::_processorObj = new StorageProcessor();

StorageController::StorageController(){
}

StorageController::~StorageController(){
}

void StorageController::updateSaveFile() {
	std::string filename = getFileName();
	std::string inputString = _processorObj->convertTaskIntoString();
	_databaseObj->executeUpdateSaveFile(filename, inputString);
}

void StorageController::programmeInitialising(){
	constructTaskLog();
	promptSaveFile();
	readSaveFile();
	std::cout << getFileName() << " is open" << endl;
}

void StorageController::promptSaveFile(){
	std::string fileName;

	if (isRetrieveSaveFile()){
		_databaseObj->readLastSavedFileFromStorage();
		fileName = _databaseObj->getLastSavedFileName();
	}
	else{
		std::cout << "Enter save file address: ";
		std::cin.ignore();
		std::getline(cin, fileName);
		_databaseObj->setLastSavedFileName(fileName);
		_databaseObj->setLastSavedFileIntoStorage(fileName);
	}
	setFileName(fileName);
}

bool StorageController::isRetrieveSaveFile(){
	std::cout << "Last saved file: " << ". Do you want to open it?  Y/N" << std::endl;
	char answer;
	bool isAnswerValid = false; 
	while (!isAnswerValid){
		std::cin >> answer;
		if (toupper(answer) == 'Y'){
			return true;
		}
		else if (toupper(answer) == 'N'){
			return false;
		}
		else{
			std::cout << "Invalid input. If you want to continue with TaskHub, enter Y" << std::endl;
			char input; 
			std::cin >> input;
			if (toupper(input) == 'Y'){
				return isRetrieveSaveFile();
			}
			else{
				exit(1);		//exit the program
			}
		}
	}
}

void StorageController::constructTaskLog(){
	taskLog = new TaskLog();
}

void StorageController::destructTaskLog(){
	taskLog->~TaskLog();
}

void StorageController::readSaveFile() {
	ifstream file;
	string currentLine;

	TaskList.clear();

	file.open(getFileName());

	while(getline(file,currentLine)) {
		TaskList.push_back(currentLine);
	}
	file.close();
}

void StorageController::setFileName(std::string fileName){
	_fileName = fileName;
}

std::string StorageController::getFileName(){
	return _fileName;
}
/*
void StorageController::setLastSaveFile(std::string newFileName){
	ofstream file;
	file.open(_lastSaveFileName);
	file << newFileName;
	file.close();
}

std::string StorageController::getLastSaveFileName(){
	ifstream file;
	std::string lastSaveFileName;
	file.open(_lastSaveFileName);
	getline(file, lastSaveFileName);
	return lastSaveFileName;

}
*/

vector<string> StorageController::returnTask() {
	return TaskList;
}
