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
	static TaskLog* taskLog;;					// For logging

	//objects to execute database and processor functions
	static StorageDatabase* _databaseObj;
	static StorageProcessor* _processorObj;

public:
	StorageController();
	~StorageController();

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
};

#endif
