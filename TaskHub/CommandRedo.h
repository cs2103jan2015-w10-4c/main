#ifndef COMMANDREDO_H_
#define COMMANDREDO_H_

#include<iostream>
#include<string>
using namespace std;

class redoChange {
public:
	redoChange ();
	~redoChange ();
	static string redo();
private:
	static const string MESSAGE_COMMAND_REDO;
	static const string MESSAGE_ERROR;
	static const string COMMAND_TYPE_ADD;
	static const string COMMAND_TYPE_DELETE;
	static const string COMMAND_TYPE_CLEAR;
	static const string COMMAND_TYPE_UPDATE;
	static const string COMMAND_TYPE_DONE;
	static const string COMMAND_TYPE_UNCOMPLETE;
};

#endif