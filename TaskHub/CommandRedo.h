#ifndef COMMANDREDO_H_
#define COMMANDREDO_H_

#include<iostream>
#include<string>
using namespace std;

class redoChange {
public:
	static string redo();
private:
	static const string MESSAGE_COMMAND_TYPE;
};

#endif