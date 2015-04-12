//@author A0111322E

#include "StorageProcessor.h"


StorageProcessor::StorageProcessor(){
}


StorageProcessor::~StorageProcessor(){
}

std::string StorageProcessor::convertTaskIntoString(){
	std::ostringstream oss;
	std::vector<Task> temp = StorageDatabase::taskHistory.getVectorTextStorage();

	if (temp.empty()){
		return "";
	}
	else{
		std::vector<Task>::iterator iter;
		int taskIndex = 1;

		for (iter = temp.begin(); iter != temp.end(); iter++){
			oss << taskIndex << ". " << iter->ToString();
			if (iter != temp.end() - 1){
				oss << std::endl;
				taskIndex++;
			}
		}
		return oss.str();
	}
}

//	Function removes the quotation marks, in the event when the user copy and paste the file address as 
//	a file path.
//	The input string is left untouched if there is no quotation marks. 
//	Condition: it is assumed that all file paths does not contain any quotation marks.
std::string StorageProcessor::processFileDirectory(std::string inputString){
	assert(&inputString != NULL);

	if (inputString[INDEX_OF_FIRST_CHAR] == '\"'){
		int stringLength = inputString.size();
		return inputString.substr(FIRST_LETTER_AFTER_QUOTATION, stringLength - NO_OF_QUOTATION_MARKS);
	}
	return inputString;
}

bool StorageProcessor::isValidFileFormat(std::string input){
	assert(&input != NULL);

	std::string fileinput = processFileDirectory(input);
	if (fileinput.size() < MIN_REQUIRED_FILE_LENGTH){				
		return false;
	}
	if (input.find_last_of(".") == std::string::npos){
		return false;
	}
	std::string extension = fileinput.substr(input.find_last_of("."));
	if (extension != ".txt"){
		return false;
	}
	return true;
}