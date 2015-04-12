//@author A0111322E
//
//	StorageDatabase is the class responsible for reading and writing of file
//	to Database. Files will be saved as .txt file format in local database 
//	such that the user can directly edit the .txt file after initialising the
//	programme. 
//
//	One of its main function is to execute the updating of the save file.
//
//	This class is also responsible for the feature in which the system will archive 
//	the name and location of the previously saved file, and allow the user to open it 
//	upon starting TaskHub just by inputting 'Y'.
//
//	_lastSavedFileStorage represents the file name of the text file that contains
//	the previously saved file.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <assert.h>
#include "History.h"

class StorageDatabase{

public:
	StorageDatabase();
	~StorageDatabase();
	static History taskHistory;

	void setLastSavedFileName(std::string filename);
	void setLastSavedFileIntoStorage(std::string newFilename);
	void readLastSavedFileFromStorage();
	std::string getLastSavedFileName();

	void executeUpdateSaveFile(std::string filename, std::string inputString);

private:
	std::string _lastSavedfile;
	static const std::string _lastSavedFileStorage;

};

