//@author A0111322E

#include "StorageController.h"

//const string messages.
const std::string StorageController::_lastSaveFileName = "LastSaveFile.txt";
const std::string StorageController::MESSAGE_ERROR_INVALID_FILE_FORMAT = "\n\tERROR: Invalid File Format.";
const std::string StorageController::MESSAGE_ERROR_LOCATION = "DETECTED AT STORAGE FILE INITIALISATION LEVEL - ";
const std::string StorageController::MESSAGE_ERROR_INVALID_ANSWER_INPUT = "ERROR: Invalid Response Input.";
const std::string StorageController::MESSAGE_ERROR_INVALID_RESUME_COMMAND_INPUT = "ERROR: Invalid Resume Command.";
const std::string StorageController::MESSAGE_TERMINATING_PROGRAM = " Terminating program..";
const std::string StorageController::MESSAGE_ANSWER_PROMPT = "Enter save file address: ";
const std::string StorageController::MESSAGE_RESUME_PROGRAM_PROMPT = "If you want to continue using TaskHub, enter Y : ";
const std::string StorageController::MESSAGE_OPEN_FILE_PROMPT = "\n\n\nDo you want to open it??  Y/N	";
const std::string StorageController::MESSAGE_ENTER_KEY_PROMPT = "\nPress [Enter] to proceed.";
const std::string StorageController::MESSAGE_DETECTED_LAST_SAVED_FILE = "\nTaskHub detected a previously saved file:\n\n   ";
const std::string StorageController::MESSAGE_OPENING_FILE_PATH = "\nOpening file path: %s";

//objects and attributes to facilitate execution of functions
std::vector<std::string> StorageController::TaskList;
std::string StorageController::_fileName;
TaskLog* StorageController::taskLog;
StorageDatabase* StorageController::_databaseObj = new StorageDatabase();
StorageProcessor* StorageController::_processorObj = new StorageProcessor();
char StorageController::buffer[255];

StorageController::StorageController(){
}

StorageController::~StorageController(){
}

void StorageController::displayFileOpeningOperation(){
	std::cout << getOpeningFilePathMessage() << endl;
	std::cout << MESSAGE_ENTER_KEY_PROMPT << endl;
}

void StorageController::printRetrieveFilePromptMessage(){
	std::cout << MESSAGE_DETECTED_LAST_SAVED_FILE;
	std::cout << _databaseObj->getLastSavedFileName();
	std::cout << MESSAGE_OPEN_FILE_PROMPT;
}

void StorageController::printResumeProgramPromptMessage(){
	std::cout << MESSAGE_RESUME_PROGRAM_PROMPT;
}

void StorageController::printAddressPromptMessage(){
	std::cout << MESSAGE_ANSWER_PROMPT;
}

std::string StorageController::getOpeningFilePathMessage(){
	sprintf_s(buffer, MESSAGE_OPENING_FILE_PATH.c_str(), getFileName().c_str());
	assert(&buffer != NULL);
	return buffer;
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

void StorageController::promptSaveFile(){
	if (isRetrieveSaveFile()){
		openLastSavedFile();
	}
	else{
		cin.ignore();
		openNewSavedFile();
	}
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
	std::string fileName = _databaseObj->getLastSavedFileName();
	assert(&fileName != NULL);
	setFileName(fileName);
}

bool StorageController::isRetrieveSaveFile(){
	printRetrieveFilePromptMessage();

	char input;
	std::cin >> input;

	try{
		char ans = _processorObj->convertToUpperCase(input);
		assert(&ans != NULL);

		if (!isValidAnswer(ans)){
			throw InvalidInputException(MESSAGE_ERROR_INVALID_ANSWER_INPUT);
		}

		assert(ans == 'Y' || ans == 'N');
		return isAnswerYes(ans);
	}
	catch (InvalidInputException& e){
		printExceptionMessage(e.what());
		logErrorMessage(e.what());
		return isRetrieveFileInvalidCaseOperation();
	}
}

bool StorageController::isRetrieveFileInvalidCaseOperation(){
	printResumeProgramPromptMessage();

	char input;
	std::cin >> input;
	std::cout << endl;

	try{
		if (toupper(input) == 'Y'){
			system("CLS");
			return isRetrieveSaveFile();
		}
		else{
			throw InvalidInputException(MESSAGE_ERROR_INVALID_RESUME_COMMAND_INPUT 
										+ MESSAGE_TERMINATING_PROGRAM);
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

bool StorageController::isValidAnswer(char input){
	return (input == 'Y' || input == 'N');
}

bool StorageController::isAnswerYes(char input){
	return (input == 'Y');
}

void StorageController::logErrorMessage(std::string errorMessage){
	std::string buffer = MESSAGE_ERROR_LOCATION + errorMessage;
	taskLog->updateTaskLog(buffer);
}