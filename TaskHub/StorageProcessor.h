//@author A0111322E
//
//	The Storage Processor is responsible for the processing and conversion of data when the 
//	Storage Controller needs further processing of the data, similar to Parser unit within the 
//	Logic component. 
//
//	One of the main functions include the ConvertTaskIntoString(), which involves conversion of 
//	the data from the save file into string, which can be stored within the program.
//
//	Other main functions include the processFileDirectory() and the isValidFileFormat, which work 
//	together to check the validity of the file path to ensure any processing of the tasks can be 
//	recorded and saved somewhere. 
//
//	After processing of the data, the data will be returned to the Storage Controller class.
//

#pragma once

#ifndef STORAGEPROCESSOR_H_
#define STORAGEPROCESSOR_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "StorageDatabase.h"

class StorageProcessor{

public:
	StorageProcessor();
	~StorageProcessor();

	std::string convertTaskIntoString();
	Task convertStringIntoTask();
	char convertToUpperCase(char input);

	std::string processFileDirectory(std::string inputString);
	bool isValidFileFormat(std::string input);


private:
	//For readability purposes
	const unsigned int MIN_REQUIRED_FILE_LENGTH = 5;
	const unsigned int FIRST_LETTER_AFTER_QUOTATION = 1;
	const unsigned int NO_OF_QUOTATION_MARKS = 2;
	const unsigned int INDEX_OF_FIRST_CHAR = 0;
	const std::string TXT_FILE_FORMAT = ".txt";

	bool isFileStorageEmpty(std::vector<Task>& FileStorage);
	std::string convertTaskIntoStringOperation(std::vector<Task>& FileStorage);

	//Sub-functions for isValidFileFormat()
	bool isMinRequiredNameLength(std::string fileInput);
	bool isContainExtensionType(std::string fileInput);
	bool isTextFileFormat(std::string fileInput);
	std::string extractExtensionTypeString(std::string fileInput);
};

#endif