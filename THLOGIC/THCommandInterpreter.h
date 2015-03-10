#ifndef THCOMMANDINTERPRETER_H_
#define THCOMMANDINTERPRETER_H_

#include <vector>
#include "THTask.h"
#include "THCommand.h"
#include "THLogging.h"

using namespace std;

// This class is used by THLogic to translate the parsed THCommand
// into the format that can be processed by THExecutor.
// Elements that are useful for THExecutor are extracted from the THCommand
// object and further processed for easy usage by the executor.
// Sample usage:
// THCommandInterpreter commandInterpreter;
// commandInterpreter.interpretAdd(addCommand, taskToBeAdded);
// _executor.addTask(taskToBeAdded);
class THCommandInterpreter {
public:
	THCommandInterpreter();
	void interpretAdd   (THCommand, THTask&);
	void interpretEdit  (THCommand, int&,THTask&);
	void interpretSearch(THCommand, vector<string>&);
	void interpretDelete(THCommand, int&);
	void interpretDone  (THCommand, int&);
	void interpretUndone(THCommand, int&);

private:
	void separateIndexDetail (string, int&, string&); 
	int  convertStringToInt  (string);

	static const int         INVALID_INDEX;
	static const string EMPTY_CONTENT;
	static const string SPACE;
	static const string NO_INDEX_EXCEPTION;
	static const string INTERPRET_ADD_LOG;  
    static const string INTERPRET_EDIT_LOG;                     
    static const string INTERPRET_DELETE_LOG;                     
    static const string INTERPRET_DONE_LOG;                       
    static const string INTERPRET_UNDONE_LOG;                      
    static const string INTERPRET_SEARCH_LOG;
};
#endif

