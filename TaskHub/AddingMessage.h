#ifndef ADDINGMESSAGE_H_
#define ADDINGMESSAGE_H_

#include<iostream>
#include<string>
using namespace std;

class AddingMessage {
public:
	static string addMessage(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_ADDED;
};

#endif