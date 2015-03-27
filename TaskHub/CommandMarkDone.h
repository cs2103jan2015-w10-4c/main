#ifndef COMMANDMARKDONE_H_
#define COMMANDMARKDONE_H_

#include<iostream>
#include<string>
using namespace std;

class markingDoneMessage {
public:
	static string markMessageDone(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_MARK_DONE;
	static const string MESSAGE_INVALID_INDEX;
};


#endif