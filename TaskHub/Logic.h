#ifndef LOGIC_H_
#define LOGIC_H_

#include <vector>
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "History.h"
using namespace std;

class Logic
{
public:
	
	static void getStorage();
	static History history;
	static vector<string> splitText(string text);

	static string printVector(vector<string> output);
	static string addTask(string input);
	static string updateTask(string input);
	static string deleteTask(string input);
	static string search(string input);
	static string display();
	static string MarkDone(string input);
	static string undo();
	static string redo();
	static string help();


	
};

#endif