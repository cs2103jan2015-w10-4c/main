//@author A0111322E

#include "StorageController.h"

std::vector<std::string> StorageController::TaskList;
std::string StorageController::_fileName;
const std::string StorageController::_lastSaveFileName = "LastSaveFile.txt";
const std::string StorageController::MESSAGE_ERROR_INVALID_FILE_FORMAT = "ERROR: Invalid File Format.";
const std::string StorageController::MESSAGE_ERROR_LOCATION = "DETECTED AT STORAGE LEVEL - ";


TaskLog* StorageController::taskLog;
StorageDatabase* StorageController::_databaseObj = new StorageDatabase();
StorageProcessor* StorageController::_processorObj = new StorageProcessor();

StorageController::StorageController(){
}

StorageController::~StorageController(){
}

void StorageController::updateSaveFile() {
	std::string filename = getFileName();
	assert(&filename != NULL);
	std::string inputString = _processorObj->convertTaskIntoString();
	_databaseObj->executeUpdateSaveFile(filename, inputString);
}

void StorageController::programmeInitialising(){
	constructTaskLog();
	_databaseObj->readLastSavedFileFromStorage();
	promptSaveFile();
	readSaveFile();
	displayFileOpeningOperation();
}

void StorageController::displayFileOpeningOperation(){
	std::string fileName = getFileName();
	assert(&fileName != NULL);
	std::cout << "\nOpening file path: " << fileName << endl;
	std::cout << "\nPress [Enter] to proceed." << endl;
}

void StorageController::promptSaveFile(){
	if (isRetrieveSaveFile()){
		openLastSavedFile();
	}
	else{
		cin.ignore();
		openNewSavedFile();
	}
}

void StorageController::printAddressPrompt(){
	std::cout << "Enter save file address: ";
}

void StorageController::openNewSavedFile(){
	printAddressPrompt();
	std::string fileName;
	std::string temp;
	std::getline(cin, temp);

	try{
		if (!_processorObj->isValidFileFormat(temp)){
			throw getErrorInvalidFileFormatMessage();
		}
		fileName = _processorObj->processFileDirectory(temp);

		assert(&fileName != NULL);
		_databaseObj->setLastSavedFileName(fileName);
		_databaseObj->setLastSavedFileIntoStorage(fileName);
		setFileName(fileName);
	}
	catch(std::string errorMessage){
		std::cout << errorMessage << "\n\n\n";
		logErrorMessage(errorMessage);
		openNewSavedFile();
	}
}

void StorageController::openLastSavedFile(){
	std::string fileName;
	_databaseObj->readLastSavedFileFromStorage();
	fileName = _databaseObj->getLastSavedFileName();
	assert(&fileName != NULL);
	setFileName(fileName);
}

bool StorageController::isRetrieveSaveFile(){
	std::cout << "\nTaskHub detected a previous save file:\n\n   " << _databaseObj->getLastSavedFileName();
	std::cout << "\n\n\nDo you want to open it??  Y/N	";
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
	std::string currentLine;

	TaskList.clear();
	std::string fileName = getFileName();
	assert(&fileName != NULL);
	file.open(fileName);

	while(getline(file,currentLine)) {
		TaskList.push_back(currentLine);
	}
	file.close();
}

void StorageController::setFileName(std::string fileName){
	assert(&fileName != NULL);
	_fileName = fileName;
}

std::string StorageController::getFileName(){
	return _fileName;
}

vector<string> StorageController::returnTask() {
	return TaskList;
}

std::string StorageController::getErrorInvalidFileFormatMessage(){
	return MESSAGE_ERROR_INVALID_FILE_FORMAT;
}

void StorageController::logErrorMessage(std::string errorMessage){
	std::string buffer = MESSAGE_ERROR_LOCATION + getErrorInvalidFileFormatMessage();
	taskLog->updateTaskLog(buffer);
}