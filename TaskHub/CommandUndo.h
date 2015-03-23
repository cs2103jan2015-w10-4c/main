#ifndef COMMANDUNDO_H_
#define COMMANDUNDO_H_

#include<iostream>
#include<string>
using namespace std;

class undoChange {
public:
	static string undo();
private:
	static const string MESSAGE_COMMAND_TYPE;
};

#endif