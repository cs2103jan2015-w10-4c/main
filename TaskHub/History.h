//@author A0115365J

//
//************************************************
//				Class History
//this class is used to temporarily store the messages in Task form during running
//it provides the basics of what the redo and undo command need
//
//************************************************

#ifndef HISTORY_H_
#define HISTORY_H_

#include <iostream>
#include <string>
#include <vector>
#include "Parser.h"
using namespace std;
class History {
private:
	vector<Task> textStorage;
	string lastCommandType;
	int lastChangedTaskIndex;
	Task lastChangedTask;
	Task lastUnchangedTask;
	vector<Task> backUpStorage;
public:
	History();
	~History();
	string printToString();
	void setVectorTextStorage(Task);
	void setVectorTextStorage(vector<Task>);
	void setLastCommandType (string);
	void setLastChangedTaskIndex (int);
	void setLastChangedTask(Task);
	void setLastUnchangedTask(Task);

	int getLastChangedTaskIndex();
	vector<Task> getVectorTextStorage();
	vector<Task> getBackUpStorage();
	Task getLastChangedTask();
	Task getLastUnchangedTask();
	string getLastCommandType();


};

#endif