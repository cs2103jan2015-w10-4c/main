#pragma once

#ifndef TEXTBUDDY_H_
#define TEXTBUDDY_H_

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_BUFERING_CAPACITY = 200;
const int TEXT_FILE_NAME = 1;
const int BEGINNING_LINE = 1;
const int CORRECT_ARGUMENT = 2;
const int NOT_FOUND = 0;

class TextBuddy {
private:
	static char buffer[MAX_BUFERING_CAPACITY];
	static vector<string> storage;

	static const string MESSAGE_ERROR_DETECTED;
	static const string MESSAGE_PROGRAMME_TERMINATED;
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_WRONG_COMMAND;
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_ADDED;
	static const string MESSAGE_DELETED;
	static const string MESSAGE_CLEARED;
	static const string MESSAGE_SORTED;
	static const string MESSAGE_CAN_FIND;
	static const string MESSAGE_CANNOT_FIND;
	static const string MESSAGE_PROMPT_COMMAND;
	static const string MESSAGE_WRONG_FORMAT;

public:
	enum CommandType {
		ADD_LINE, 
		DISPLAY_ALL, 
		DELETE_LINE, 
		CLEAR_ALL, 
		SORT, 
		SEARCH, 
		EXIT, 
		INVALID
	};
	static void main(int argc, char* argv[]);

	static string addLine(string fileName, string message);
	static string deleteLine(string fileName, string message);
	static string displayAll(string fileName);
	static string clearAll(string fileName);
	static string sortLineAlphabetically(string fileName);
	static string searchForWord(string fileName, string message);
	static string searchForLine(string fileName, string message, string lineNumber);

	static string executeCommand(string fileName, string userCommand);
	static string removeFirstWord(string command);
	static string getFirstWord(string command);
	static string getUserCommand();

	static void getUserInput(string fileName);
	static void writeToFile(string fileName);
	static void printLine(int i, string line);
	static void showToUser(string text);

	static void checkCommandLineInput(int argc);
	static void initialStorage(string fileName);

	static bool isValidInput(string message);
	static vector<string>::iterator getLineIterator(string fileName, string message);
	static CommandType determineCommandType(string userCommand);

	static string checkCommandType(TextBuddy::CommandType command);
};

#endif;