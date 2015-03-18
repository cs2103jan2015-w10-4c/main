#ifndef COMMANDDISPLAY_H_
#define COMMANDDISPLAY_H_

#include<iostream>
#include<string>
using namespace std;

class CommandDisplay {
public:
	static string display();
private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif