#ifndef MARKDONEMESSAGE_H_
#define MARKDONEMESSAGE_H_

#include<iostream>
#include<string>
using namespace std;

class markingDoneMessage {
public:
	static string markMessageDone(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif