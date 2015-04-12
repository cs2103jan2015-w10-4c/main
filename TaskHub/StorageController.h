//@author A0111322E

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
