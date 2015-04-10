#include "StorageProcessor.h"


StorageProcessor::StorageProcessor(){
}


StorageProcessor::~StorageProcessor(){
}

std::string StorageProcessor::convertTaskIntoString(){
	std::ostringstream oss;
	std::vector<Task> temp = Logic::history.getVectorTextStorage();

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