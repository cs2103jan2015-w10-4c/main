#include "StorageController.h"

vector<string> StorageController::TaskList;
std::string StorageController::_fileName;
TaskLog* StorageController::taskLog;

StorageController::StorageController(){
}

StorageController::~StorageController(){
}

//change function name to updateSaveFile
void StorageController::programmeTerminating() {
	ofstream file;

	file.open(getFileName());
	file << convertTaskIntoString();	
	file.close();
}

std::string StorageController::convertTaskIntoString(){
	ostringstream oss;
	vector<Task> temp = Logic::history.getVectorTextStorage();

	if (temp.empty()){
		return "";
	}
	else{
		std::vector<Task>::iterator iter;
		int taskIndex = 1;
		
		for (iter = temp.begin(); iter != temp.end(); iter++){
			oss << taskIndex << ". " << iter->ToString();
			if (iter != temp.end() - 1){
				oss << std::endl;
				taskIndex++;
			}
		}
		return oss.str();
	}
}

void StorageController::programmeInitialising(){
	constructTaskLog();
	promptSaveFile();
	readSaveFile();
}

void StorageController::promptSaveFile(){
	std::cout << "Enter save file address: ";
	std::string fileName;
	std::cin >> fileName;
	setFileName(fileName);
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

vector<string> StorageController::returnTask() {
	return TaskList;
}

