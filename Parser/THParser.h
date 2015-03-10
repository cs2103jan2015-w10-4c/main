#ifndef THPARSER_H
#define THPARSER_H

#include <string>
#include "THMainParser.h"
#include "THCommand.h"

//THParser is the facade class of the Parser component

class THParser {
public:
	THParser();

	void parseInput(std::string);
	THCommand retrieveCommand();

private:
	THMainParser _mainParser;
};
#endif