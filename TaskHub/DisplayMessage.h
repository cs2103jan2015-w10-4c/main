#ifndef DISPLAYMESSAGE_H_
#define DISPLAYMESSAGE_H_

#include<iostream>
#include<string>
using namespace std;

class displayingMessage {
public:
	static string displayMessage();
private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif