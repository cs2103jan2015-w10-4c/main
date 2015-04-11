#include "StorageDatabase.h"

const std::string StorageDatabase::_lastSavedFileStorage = "LastSavedFile.txt";

StorageDatabase::StorageDatabase(){
}


StorageDatabase::~StorageDatabase(){
}

void StorageDatabase::setLastSavedFileName(std::string filename){
	_lastSavedfile = filename;
}

std::string StorageDatabase::getLastSavedFileName(){
	return _lastSavedfile;
}

void StorageDatabase::setLastSavedFileIntoStorage(std::string newFileName){
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
	std::ofstream file;
	file.open(filename);
	file << inputString;
	file.close();
}