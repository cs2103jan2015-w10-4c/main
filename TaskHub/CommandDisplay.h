#ifndef COMMANDDISPLAY_H_
#define COMMANDDISPLAY_H_

#include<iostream>
#include<string>
using namespace std;

class CommandDisplay {
public:
	static string display(string message);
	static vector<string> messageDisplayed;
private:
	static const string MESSAGE_DISPLAYED;
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_EMPTY_FILE;
	
};


#endif