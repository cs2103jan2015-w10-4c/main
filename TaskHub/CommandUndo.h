//@author A0115365J

#ifndef COMMANDUNDO_H_
#define COMMANDUNDO_H_

#include<iostream>
#include<string>
using namespace std;

class undoChange {
public:
	undoChange ();
	~undoChange ();
	static string undo();
private:
	static const string MESSAGE_COMMAND_UNDO;
	static const string MESSAGE_ERROR;
	static const string COMMAND_TYPE_ADD;
	static const string COMMAND_TYPE_DELETE;
	static const string COMMAND_TYPE_CLEAR;
	static const string COMMAND_TYPE_UPDATE;
	static const string COMMAND_TYPE_DONE;
	static const string COMMAND_TYPE_UNCOMPLETE;
};

#endif