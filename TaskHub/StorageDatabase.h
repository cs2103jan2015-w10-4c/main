#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class StorageDatabase{

public:
	StorageDatabase();
	~StorageDatabase();

	void setLastSavedFileName(std::string filename);
	void setLastSavedFileIntoStorage(std::string newFilename);
	void readLastSavedFileFromStorage();
	std::string getLastSavedFileName();

	void executeUpdateSaveFile(std::string filename, std::string inputString);

private:
	std::string _lastSavedfile;
	static const std::string _lastSavedFileStorage;
};

