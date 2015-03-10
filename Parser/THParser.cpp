//@author A0097547M

#include <string>
#include "THParser.h"
#include "THMainParser.h"
#include "THCommand.h"
#include "THLogging.h"

using namespace std;

const string LOG_PARSEINPUT = "THParser::parseInput is called, received ";
const string LOG_RETRIEVECOMMAND = "THParser::retrieveCommand is called";

THParser::THParser() {
}

 void THParser::parseInput(string inputString) {
	 THLogging& Logging = THLogging::getInstance();
	 Logging.addLog(LOG_PARSEINPUT + inputString);
	 Logging.saveLog();

	 _mainParser.parseInput(inputString);
}

THCommand THParser::retrieveCommand() {
	THLogging& Logging = THLogging::getInstance();
	Logging.addLog(LOG_RETRIEVECOMMAND);
	 Logging.saveLog();

	return _mainParser.retrieveCommand();
}