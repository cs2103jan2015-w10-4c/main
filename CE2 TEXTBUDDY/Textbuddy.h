// Student: Liao Dianze
// Matriculation Card: A0115365J
// Tutorial Group: w10

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
	static const string MESSAGE_SORTING_ERROR;

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
	// input: int argc, char* argv[]
	// output: to create a file with name that user define, and pass it to a fucntion
	//		   to get further commands, if the command line input is valid.
	// return: NIL
	
	static string addLine(string fileName, string message);
	// input: string fileName, string message
	// output: add the message to fileNanme.txt if the message is valid, else do nothing
	// return: a message that shows success or failure

	static string deleteLine(string fileName, string message);
	// input: string fileName, string message
	// output: delete the message if it is valid, else do nothing
	// return: a message that shows success or failure
	// assumption: user only deletes line in range, i.e. if there are only 3 messages the maximum
	//			   number the user can do is "delete 3", while a "4" will create errors in the programme

	static string displayAll(string fileName);
	// input: string fileName
	// output: display all the messages in fileNanme.txt if there are messages, else do nothing
	// return: a message that shows success or failure

	static string clearAll(string fileName);
	// input: string fileName
	// output: clear all the messages in fileNanme.txt
	// return: a message that shows success

	static string sortLineAlphabetically(string fileName);
	// input: string fileName
	// output: sort the messages in fileName.txt in alphabetical order if there are messages
	// return: a message that shows success or failure

	static string searchForWord(string fileName, string message);
	// input: string fileName, string message
	// output: search for the word(s) in the message and print out the message number and the message if found
	// return: a message that shows success or failure

	static string searchForLine(string fileName, string message, string lineNumber);
	// input: string fileName, string message, string lineNumber
	// output: search for the line number, and return if any, or an empty string if nothing is found
	// return: an empty string is not found, the line number if found

	static string executeCommand(string fileName, string userCommand);
	// input: string fileName, string userCommand
	// output: identify the command and the message and pass it to the correct function
	// return: a message of success of failure if the command is valid, or invalid command

	static string removeFirstWord(string command);
	// input: string command
	// output: identify the message 
	// return: the  message if the message is valid, or an empty string if it is not

	static string getFirstWord(string command);
	// input: string command
	// output: identify the command i.e. add, delete etc.
	// return: the command
	// assumption: the user must key in at least one word, i.e. he cannot directly press ENTER in "command: " interface

	static string getUserCommand();
	// input: NIL
	// output: get in user input
	// return: the user input

	static void getUserInput(string fileName);
	// input: string fileName
	// output: pass userCommand got to designated function and 
	//         to show the requested feedback if execution is successful
	// return: NIL

	static void writeToFile(string fileName);
	// input: string fileName
	// output: write the messages stored in vector to fileName.txt 
	// return: NIL

	static void printLine(int i, string line);
	// input: int i, string line
	// output: print out the message number and the message
	// return: NIL

	static void showToUser(string text);
	// input: string fileName
	// output: print out the text
	// return: NIL

	static void checkCommandLineInput(int argc);
	// input: int argc
	// output: a message indicating true or false command line input
	// return: NIL

	static void initialStorage(string fileName);
	// input: string fileName
	// output: initialise the vector and *.txt 
	// return: NIL


	static bool isValidInput(string message);
	// input: string fileName
	// output: determine the message is empty
	// return: true if the message is not empty

	static vector<string>::iterator getLineIterator(string fileName, string message);
	// input: string fileName, string message
	// output: get the message iterator for later usage
	// return: the message iterator

	static CommandType determineCommandType(string userCommand);
	// input: string userCommand
	// output: determine the user command for the correct implementation
	// return: comand type

	// for testing purpose
	static string checkCommandType(TextBuddy::CommandType command);
	// input: string command
	// output: check the command returned is correct or not
	// return: the command
};

#endif;