//@author A0111322E

#include "StorageController.h"

std::vector<std::string> StorageController::TaskList;
std::string StorageController::_fileName;
const std::string StorageController::_lastSaveFileName = "LastSaveFile.txt";
const std::string StorageController::MESSAGE_ERROR_INVALID_FILE_FORMAT = "\n\tERROR: Invalid File Format.";
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

void StorageController::printAddressPromptMessage(){
	std::cout << "Enter save file address: ";
}

void StorageController::printExceptionMessage(std::string message){
	assert(&message != NULL);
	std::cout << message << "\n\n\n";
}

void StorageController::fileNameSettingOperation(std::string fileName){
	assert(&fileName != NULL);
	_databaseObj->setLastSavedFileName(fileName);
	_databaseObj->setLastSavedFileIntoStorage(fileName);
	setFileName(fileName);
}

void StorageController::openNewSavedFile(){
	printAddressPromptMessage();
	std::string fileName;
	std::string temp;
	std::getline(cin, temp);

	try{
		if (!_processorObj->isValidFileFormat(temp)){
			throw InvalidInputException(MESSAGE_ERROR_INVALID_FILE_FORMAT);
		}

		fileName = _processorObj->processFileDirectory(temp);
		assert(&fileName != NULL);
		fileNameSettingOperation(fileName);
	}
	catch(InvalidInputException& e){
		printExceptionMessage(e.what());
		logErrorMessage(e.what());
		openNewSavedFile();
	}
}

void StorageController::openLastSavedFile(){
	_databaseObj->readLastSavedFileFromStorage();

	std::string fileName;
	fileName = _databaseObj->getLastSavedFileName();
	assert(&fileName != NULL);

	setFileName(fileName);
}

bool StorageController::isValidAnswer(char input){
	return (input == 'Y' || input == 'N');
}

bool StorageController::isAnswerYes(char input){
	return (input == 'Y');
}

void StorageController::printRetrieveFilePromptMessage(){
	std::cout << "\nTaskHub detected a previously saved file:\n\n   " << _databaseObj->getLastSavedFileName();
	std::cout << "\n\n\nDo you want to open it??  Y/N	";
}

bool StorageController::isRetrieveSaveFile(){
	printRetrieveFilePromptMessage();
	char input;
	std::cin >> input;

	try{
		char ans = _processorObj->convertToUpperCase(input);
		assert(&ans != NULL);

		if (!isValidAnswer(ans)){
			throw InvalidInputException("Invalid response input.");
		}

		assert(ans == 'Y' || ans == 'N');
		if (isAnswerYes(ans)){
			return true;
		}
		else{
			return false;
		}
	}
	catch (InvalidInputException& e){
		printExceptionMessage(e.what());
		logErrorMessage(e.what());
		return isRetrieveFileInvalidCaseOperation();
	}
	/*
	if (toupper(ans) == 'Y'){
		return true;
	}
	else if (toupper(ans) == 'N'){
		return false;
	}
	else{
		std::cout << "Invalid input. If you want to continue with TaskHub, enter Y : ";
		char input; 
		std::cin >> input;
		std::cout << endl;
		if (toupper(input) == 'Y'){
			system("CLS");
			return isRetrieveSaveFile();
		}
		else{
			exit(1);		//exit the program
		}
	}
	*/
}

bool StorageController::isRetrieveFileInvalidCaseOperation(){
	std::cout << "If you want to continue using TaskHub, enter Y : ";
	char input;
	std::cin >> input;
	std::cout << endl;

	try{
		if (toupper(input) == 'Y'){
			system("CLS");
			return isRetrieveSaveFile();
		}
		else{
			throw InvalidInputException("Invalid resume command. Exiting function");
		}
	}
	catch (InvalidInputException& e){
		printExceptionMessage(e.what());
		logErrorMessage(e.what());
		exit(1);
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

void StorageController::logErrorMessage(std::string errorMessage){
	std::string buffer = MESSAGE_ERROR_LOCATION + errorMessage;
	taskLog->updateTaskLog(buffer);
}