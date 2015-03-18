#ifndef DELETINGMESSAGE_H_
#define DELETINGMESSAGE_H_

#include<iostream>
#include<string>
using namespace std;

class deletingMessage {
public:
	static string deleteMessage(string input);

private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif