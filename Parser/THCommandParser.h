#ifndef THCOMMANDPASER_H
#define THCOMMANDPASER_H
#include <string>
using namespace std;

class THCommandParser
{
public:
	THCommandParser();
	THUtility::CommandType getCommand();
	string getContent();
private:
	THUtility::CommandType _commandtype;
	string _unusedContent;
	void determineCommandType(string);
	string getFirstWord(string);
};
#endif

