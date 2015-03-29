#include "Logic.h"
#include "Parser.h"
#include "CommandDisplay.h"
#include "CommandAutoSort.h"

const string CommandDisplay::MESSAGE_COMMAND_TYPE="display";
const string CommandDisplay::MESSAGE_EMPTY_FILE="The file is empty";

string CommandDisplay::display(string message) {

	if (Logic::history.getVectorTextStorage().empty()){
		sprintf_s(Logic::messageDisplayed,MESSAGE_EMPTY_FILE.c_str());
		return Logic::messageDisplayed;

	} else {
		CommandAutoSort::autoSort();
		ostringstream totalTask;
		
		if (message=="all"||message=="display") {
		
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() - 1; i++){
				ostringstream oss;
			
				oss << i + 1 << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				totalTask << TaskDisplay;
		}

		int size = Logic::history.getVectorTextStorage().size();
		totalTask << size << ". " << Logic::history.getVectorTextStorage()[size - 1].ToString();
		
		} else if (message=="floating") {
			int taskNo=1;
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() ; i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getTaskType()=="floating")
				oss << taskNo << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				totalTask << TaskDisplay;
				taskNo++;
			}

		} else if (message=="deadline") {
			int taskNo=1;
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() ; i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getTaskType()=="deadline")
				oss << taskNo << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				totalTask << TaskDisplay;
				taskNo++;
			}

		} else if (message=="timed") {
			int taskNo=1;
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size(); i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getTaskType()=="timed")
				oss << taskNo << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				totalTask << TaskDisplay;
				taskNo++;
			}

		} else if (message=="done") {
			int taskNo=1;
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size(); i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getStatus()=="done")
				oss << taskNo << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				totalTask << TaskDisplay;
				taskNo++;
			}

		} else if (message=="uncompleted") {
			int taskNo=1;
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size(); i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getStatus()=="uncompleted")
				oss << taskNo << ". " << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				totalTask << TaskDisplay;
				taskNo++;
			}

		} else {

			totalTask << "invalid display command";
		}

		return totalTask.str();
	}
	
}