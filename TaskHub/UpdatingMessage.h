#ifndef UPDATINGMESSAGE_H_
#define UPDATINGMESSAGE_H_

#include<iostream>
#include<string>
using namespace std;

class UpdatingMessage {
public:
	static string updateMessage(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
};

#endif