//@author A0111322E

#include "StorageDatabase.h"

//_lastSavedFileStorage represents the file name of the text file that contains the previously saved file.
const std::string StorageDatabase::_lastSavedFileStorage = "LastSavedFile.txt";	

History StorageDatabase::taskHistory;

StorageDatabase::StorageDatabase(){
}


StorageDatabase::~StorageDatabase(){
}

void StorageDatabase::setLastSavedFileName(std::string filename){
	assert(&filename != NULL);
	_lastSavedfile = filename;
}

std::string StorageDatabase::getLastSavedFileName(){
	return _lastSavedfile;
}

void StorageDatabase::setLastSavedFileIntoStorage(std::string newFileName){
	assert(&newFileName != NULL);
	std::ofstream file;
	file.open(_lastSavedFileStorage);
	file << newFileName;
	file.close();
}

void StorageDatabase::readLastSavedFileFromStorage(){
	std::ifstream file;
	std::string readString;
	file.open(_lastSavedFileStorage);
	getline(file, readString);
	setLastSavedFileName(readString);
}

void StorageDatabase::executeUpdateSaveFile(std::string filename, std::string inputString){
	assert(&filename != NULL);
	assert(&inputString != NULL);
	std::ofstream file;
	file.open(filename);
	file << inputString;
	file.close();
}