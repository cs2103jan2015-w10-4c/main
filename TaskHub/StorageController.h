//@author A0111322E
//	
//	StorageController acts as the 'brain' or central unit within the storage component.
//	It essentially handles the storing of the different tasks that have been archived 
//	by the user.
//
//	This class will rely on StorageProcessor and StorageDatabase to execute the different
//	types of functions within the Storage component. This is done by calling on the two
//	objects within this class: _databaseObj & _processorObj, each responsible for the 
//	calling of functions within the respectively assigned classes. 
//

#ifndef STORAGECONTROLLER_H_
#define STORAGECONTROLLER_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "TaskLog.h"
#include "StorageProcessor.h"
#include "StorageDatabase.h"

class StorageController {
private:
	static std::vector<std::string> TaskList;
	static std::string _fileName;
	const static std::string _lastSaveFileName;

	//objects to execute database and processor functions
	static StorageDatabase* _databaseObj;
	static StorageProcessor* _processorObj;

	// for readability purposes
	static const std::string MESSAGE_ERROR_INVALID_FILE_FORMAT;
	static const std::string MESSAGE_ERROR_LOCATION;
	static const std::string MESSAGE_ERROR_INVALID_ANSWER_INPUT;
	static const std::string MESSAGE_ERROR_INVALID_RESUME_COMMAND_INPUT;
	static const std::string MESSAGE_TERMINATING_PROGRAM;

	static void logErrorMessage(std::string errorMessage);
	static void printAddressPromptMessage();
	static void printRetrieveFilePromptMessage();
	static void printResumeProgramPromptMessage();
	static void printExceptionMessage(std::string message);
	static void fileNameSettingOperation(std::string fileName);
	static bool isRetrieveFileInvalidCaseOperation();
	static bool isValidAnswer(char ans);
	static bool isAnswerYes(char ans);

public:
	StorageController();
	~StorageController();

	// for logging
	static TaskLog* taskLog;;					
	static void constructTaskLog();
	static void destructTaskLog();

	static void programmeInitialising();
	static void updateSaveFile(); 
	static void readSaveFile();
	static void promptSaveFile();
	static void displayFileOpeningOperation();
	static std::vector<std::string> returnTask();

	static void setFileName(std::string fileName);
	static std::string getFileName();
	static void setLastSaveFile(std::string newFileName);
	static std::string getLastSaveFileName();

	static std::string convertTaskIntoString();
	static bool isRetrieveSaveFile();

	static void openLastSavedFile();
	static void openNewSavedFile();
	
};

// exception class
class InvalidInputException : public std::exception{
private:
	std::string _message;

public:
	InvalidInputException(std::string msg){
		_message = msg;
	}

	//overwrite the what function
	virtual const char* what() const throw(){
		return _message.c_str();
	}
};

#endif
