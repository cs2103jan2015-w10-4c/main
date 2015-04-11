#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class StorageDatabase{

public:
	StorageDatabase();
	~StorageDatabase();

	void executeUpdateSaveFile(std::string filename, std::string inputString);
};

