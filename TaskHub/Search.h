#ifndef SEARCH_H_
#define SEARCH_H_

#include<iostream>
#include<string>
using namespace std;

class searchingMessage {
public:
	static string searchMessage(string input);
private:
	static const string MESSAGE_COMMAND_TYPE;
};


#endif