//@author A0111322E

#pragma once

#ifndef STORAGEPROCESSOR_H_
#define STORAGEPROCESSOR_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstddef>
#include "StorageDatabase.h"

class StorageProcessor{

public:
	StorageProcessor();
	~StorageProcessor();

	std::string convertTaskIntoString();
	Task convertStringIntoTask();

	std::string processFileDirectory(std::string inputString);
	bool isValidFileFormat(std::string input);

};

#endif