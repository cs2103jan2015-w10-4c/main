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

	static const std::string MESSAGE_ERROR_INVALID_FILE_FORMAT;
	static const std::string MESSAGE_ERROR_LOCATION;
	static std::string getErrorInvalidFileFormatMessage();
	static void logErrorMessage(std::string errorMessage);
	static void printAddressPrompt();

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

#endif
