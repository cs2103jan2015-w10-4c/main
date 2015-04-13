//@author A0115365J
//
//************************************************
//				Class markingDoneMessage
//this class is used when the done command is called
//it will change the tasks' status to done
//
//************************************************

#ifndef COMMANDMARKDONE_H_
#define COMMANDMARKDONE_H_

#include<iostream>
#include<string>
using namespace std;

class markingDoneMessage {
public:
	markingDoneMessage ();
	~markingDoneMessage ();
	static string markMessageDone(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_MARK_DONE;
	static const string MESSAGE_INVALID_INDEX;
};


#endif