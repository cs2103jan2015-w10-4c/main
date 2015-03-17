#ifndef LOGIC_H_
#define LOGIC_H_

#include <vector>
#include <string>
#include "Parser.h"
#include "Storage.h"
using namespace std;

class Logic
{
public:
	
	static string getFirstWord(string input);
	static string removeFirstWord(string input);
	static vector<string> splitText(string text);
	static string printVector(vector<string> output);
	
	static vector<Textbody> list;
	static string lastCommandType;
	static int lastChangedTextbodyIndex;
	static Textbody lastUnchangedTextbody;
	static Textbody lastChangedTextbody;


	static void getStorage();

	static string addTextbody(string input);
	static string updateTextbody(string input);
	static string deleteTextbody(string input);
	static string search(string input);
	static string display();
	static string MarkDone(string input);
	
	static string undo();
	static string redo();
};

#endif