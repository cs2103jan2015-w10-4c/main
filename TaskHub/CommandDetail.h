#ifndef COMMANDDETAIL_H_
#define COMMANDDETAIL_H_

#include<iostream>
#include<string>

using namespace std;

class CommandDetail
{
public:
	static string detailMessage(string taskIndex);
	static bool checkInputValidation(string taskIndex);
	static string FEEDBACK_SYSTEM;

private:
	static const string MESSAGE_COMMAND_TYPE;
	static const string MESSAGE_INVALID_INDEX;
	static const string MESSAGE_DETAIL;

};

#endif

