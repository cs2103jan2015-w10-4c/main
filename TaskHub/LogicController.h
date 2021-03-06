//@author A0115365J

//
//************************************************
//				Class Logic
//this class is used for internal traffic flow, it will direct to the messages to appropriate commands
//
//
//************************************************

#ifndef LOGIC_H_
#define LOGIC_H_

#include <vector>
#include <string>
#include "Parser.h"
#include "StorageController.h"
#include "History.h"
using namespace std;

const int MAX_BUFFERRING_CAPACITY=10086;
class Logic{

public:
	
	static char messageDisplayed[MAX_BUFFERRING_CAPACITY];
	static string getFirstWord(string input);
	static string removeFirstWord(string input);
	
	static string checkClash(string input);
	static string addTask(string input);
	static string updateTask(string input);
	static string deleteTask(string input);
	static string search(string input);
	static string clearAll (string input);
	static string display(string message);
	static string MarkDone(string input);
	static string markUncompleted (string input);
	static string undo();
	static string redo();
	static string sort();
	static string help();
	static string recurTask(string input);
	static string show(string input);
	static string getDetail(string input);
	
	static vector<Task> textStorage;
	static string lastCommandType;
	static int lastChangedTaskIndex;
	static Task lastUnchangedTask;
	static Task lastChangedTask;

	static void getStorage();
};

#endif