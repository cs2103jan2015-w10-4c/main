#pragma once

#ifndef STORAGEPROCESSOR_H_
#define STORAGEPROCESSOR_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstddef>
#include "Logic.h"

class StorageProcessor{

public:
	StorageProcessor();
	~StorageProcessor();

	std::string convertTaskIntoString();
	std::string processFileDirectory(std::string inputString);

};

#endif