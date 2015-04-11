#include "StorageDatabase.h"


StorageDatabase::StorageDatabase(){
}


StorageDatabase::~StorageDatabase(){
}


void StorageDatabase::executeUpdateSaveFile(std::string filename, std::string inputString){
	std::ofstream file;
	file.open(filename);
	file << inputString;
	file.close();
}