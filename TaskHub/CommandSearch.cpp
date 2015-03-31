#include "Logic.h"
#include "Parser.h"
#include "CommandSearch.h"
#include <algorithm>

const string CommandSearch::MESSAGE_COMMAND_TYPE="search";
const string CommandSearch::MESSAGE_CANNOT_FIND="Cannot find message";
const string CommandSearch::MESSAGE_EMPTY_FILE="The file is empty";


void filterByDate(string input,vector<Task> &output) {
	size_t get_date=input.find("/");
	int taskMonth;
	int taskDay;
	vector<Task> temp=Logic::history.getVectorTextStorage();
	int size=Logic::history.getVectorTextStorage().size();
	if (get_date!=string::npos) {
			 taskMonth=atoi(input.substr(get_date+1,2).c_str());
			 taskDay=atoi(input.substr(get_date-2,2).c_str());
			 for ( int i=0;i<size;i++) {
				if (taskMonth==temp[i].getIntegerMonth()) {
					if (taskDay==temp[i].getIntegerDay()) {
						output.push_back(temp[i]);
					}
				}
			}
		}
	
	if (output.empty()) {
		output=temp;
	}
	return;
}
void filterByTaskName(string input, vector<Task> &output) {
	int size=output.size();
	vector<Task> newOutput;
	string description=input.substr(0,input.find_first_of("0123456789"));
	transform(input.begin(),input.end(),input.begin(),:: tolower);

		for ( int i = 0; i < size; i++){
			if (description==output[i].getTaskName()) {
				newOutput.push_back(output[i]);
			}
			}
		if (!newOutput.empty()) {
			output=newOutput;
		}
		
	return;
}

void filterByTime(string input, vector<Task> &output) {
		size_t get_start_time=input.find_first_of(":");
		int size=output.size();
		int startTaskMinute;
		int startTaskHour;
		vector<Task> newOutput;
	if (get_start_time!=string::npos) {
			startTaskMinute=atoi(input.substr(get_start_time+1,2).c_str());
			startTaskHour=atoi(input.substr(get_start_time-2,2).c_str());
			for ( int i=0;i<size;i++) {
				if (startTaskHour==output[i].getIntegerMonth()) {
					if (startTaskHour==output[i].getIntegerDay()) {
						newOutput.push_back(output[i]);
					}
				}
			}
		}
	if (!newOutput.empty()) {
		output=newOutput;
	}

	return;
}
/*
void filterByVenue(string input, vector<Task> &output) {
	size_t get_venue=input.find("@");
	string venue=input.substr(get_venue+1,input.find("..."));
	int size=output.size();
	vector<Task>newOutput;
	if (get_venue!=string::npos) {
			 
			 for (unsigned int i=0;i<size;i++) {
				 if (venue==output[i].getVenue()) {
						output.push_back(output[i]);
					}
				}
		}
	
	if (newOutput.empty()) {
		output=newOutput;
	}

	return;
}
*/
string CommandSearch::searchMessage (string input) {

	if (Logic::history.getVectorTextStorage().empty()){
		sprintf_s(Logic::messageDisplayed,MESSAGE_EMPTY_FILE.c_str());
		return Logic::messageDisplayed;
	}
	else{
		vector<Task> output;
		//vector<string> output;
		vector<Task> temp=Logic::history.getVectorTextStorage();
		vector<string> description;
		vector <int> taskIndex;
	
		//size_t get_date=input.find("/");
		//size_t get_time=input.find(":");
		//int size=temp.size();

		filterByDate(input,output);
		filterByTaskName(input,output);
		filterByTime(input,output);
		//ostringstream totalTask;
		for (unsigned int i=0;i<output.size();i++) {
			//ostringstream oss;
				cout << i+1 << ". " << output[i].ToString() << endl;
				//string TaskDisplay = oss.str();
				//totalTask << TaskDisplay;

		}
		return "";
		//filterByVenue(input,output);
		/*
		int taskMinute;
		int taskHour;
		
		
		
		if ((get_time==string::npos)&&(get_date!=string::npos)) {
			
		
		} //when no dates are enter, by default it is today	
		else if ((get_time!=string::npos)&&(get_date==string::npos)) {

			for (int i=0;i<size;i++) {
				if (taskMonth==temp[i].getIntegerMonth()) {
					if (taskDay==temp[i].getIntegerDay()) {
						if (taskHour==temp[i].getHour()) {
					//if (currentMinute==temporary[i].getMinute()) {
					taskIndex.push_back(i);
					//}
						}
					}
				}
			}
		} else if ((get_time!=string::npos)&&(get_date!=string::npos)) {
			for (int i=0;i<size;i++) {
				if (taskMonth==temp[i].getIntegerMonth()) {
					if (taskDay==temp[i].getIntegerDay()) {
						if (taskHour==temp[i].getHour()) {
					//if (currentMinute==temporary[i].getMinute()) {
						taskIndex.push_back(i);
					//}
						}
					}
				}
			}
		}

		if ((get_date==string::npos)&&(get_time==string::npos)){
		// search by taskname
		transform(input.begin(),input.end(),input.begin(),:: tolower);

		for (unsigned int i = 0; i < temp.size(); i++){
			string _Taskname = (temp[i]).getTaskName();
			transform(_Taskname.begin(),_Taskname.end(),_Taskname.begin(),:: tolower);
			description.push_back(_Taskname);
		}
		
		for (unsigned int j = 0; j < description.size(); j++){
			size_t found= description[j].find(input);	
			if (found!=string::npos){
					ostringstream oss;
					oss << j + 1 << "." << temp[j].ToString() << endl;
					string TaskDisplay = oss.str();
					output.push_back(TaskDisplay);
				}
			}
		}
		if (output.empty()) {
			sprintf_s(Logic::messageDisplayed, MESSAGE_CANNOT_FIND.c_str());
			return Logic::messageDisplayed;
		} else {
		return CommandSearch::printVector(output);
		}*/	

	}
}

string CommandSearch::printVector(vector<string> output){
	ostringstream oss;
	for (unsigned int i = 0; i < output.size(); i++){
		oss << output[i];
	}
	return oss.str();
}

