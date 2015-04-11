#include "Logic.h"
#include "Parser.h"
#include "CommandDisplay.h"
#include "CommandAutoSort.h"


const string CommandDisplay::MESSAGE_ALL = "all";
const string CommandDisplay::MESSAGE_DISPLAY_WORD = "display";
const string CommandDisplay::MESSAGE_COMMAND_TYPE = "display";
const string CommandDisplay::MESSAGE_INVALID_COMMAND = "invalid display command";
const string CommandDisplay::MESSAGE_EMPTY_FILE = "The file is now empty";
const string CommandDisplay::MESSAGE_DISPLAYED = "Displayed successful";
const string CommandDisplay::STATUS_UNCOMPLETE = "uncompleted";
const string CommandDisplay::STATUS_DONE = "done";
const string CommandDisplay::TASK_TYPE_TIMED = "timed";
const string CommandDisplay::TASK_TYPE_DEADLINE = "deadline";
const string CommandDisplay::TASK_TYPE_FLOATING = "floating";
const string CommandDisplay::DOT = ". ";

vector <string> CommandDisplay::messageDisplayed;

CommandDisplay::CommandDisplay () {

}
CommandDisplay::~CommandDisplay() {

}

string CommandDisplay::display(string message) {
		messageDisplayed.clear();
	if (Logic::history.getVectorTextStorage().empty()){
		sprintf_s(Logic::messageDisplayed,MESSAGE_EMPTY_FILE.c_str());
		return Logic::messageDisplayed;

	} else {
		
		transform(message.begin(),message.end(),message.begin(), ::tolower);
		if (message == MESSAGE_ALL||message == MESSAGE_DISPLAY_WORD) {
		
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() - 1; i++){
				ostringstream oss;
				
				oss << i + 1 << DOT << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				messageDisplayed.push_back( TaskDisplay);
		}
		ostringstream oss;
		
		int size = Logic::history.getVectorTextStorage().size();
		oss << size << DOT << Logic::history.getVectorTextStorage()[size - 1].ToString();
		string TaskDisplay = oss.str();
		messageDisplayed.push_back( TaskDisplay);
		
		} else if (message == TASK_TYPE_FLOATING) {
			int taskNo = 1;
			messageDisplayed.clear();
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() ; i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getTaskType() == TASK_TYPE_FLOATING)
				oss << taskNo << DOT << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				messageDisplayed.push_back( TaskDisplay);
				taskNo++;
			}

		} else if (message == TASK_TYPE_DEADLINE) {
			int taskNo = 1;
			messageDisplayed.clear();
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size() ; i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getTaskType() == TASK_TYPE_DEADLINE)
				oss << taskNo << DOT << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				messageDisplayed.push_back( TaskDisplay);
				taskNo++;
			}

		} else if (message == TASK_TYPE_TIMED) {
			int taskNo=1;
			messageDisplayed.clear();
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size(); i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getTaskType() == TASK_TYPE_TIMED)
				oss << taskNo << DOT << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				messageDisplayed.push_back( TaskDisplay);
				taskNo++;
			}

		} else if (message == STATUS_DONE) {
			int taskNo = 1;
			messageDisplayed.clear();
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size(); i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getStatus() == STATUS_DONE)
				oss << taskNo << DOT << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				messageDisplayed.push_back( TaskDisplay);
				taskNo++;
			}

		} else if (message == STATUS_UNCOMPLETE) {
			int taskNo = 1;
			messageDisplayed.clear();
			for (unsigned int i = 0; i < Logic::history.getVectorTextStorage().size(); i++){
			ostringstream oss;
			if (Logic::history.getVectorTextStorage()[i].getStatus() == STATUS_UNCOMPLETE)
				oss << taskNo << DOT << Logic::history.getVectorTextStorage()[i].ToString() << endl;
				string TaskDisplay = oss.str();
				messageDisplayed.push_back( TaskDisplay);
				taskNo++;
			}

		} else {

			return MESSAGE_INVALID_COMMAND;
		}
	
		return CommandDisplay::MESSAGE_DISPLAYED;
	}
	
}

