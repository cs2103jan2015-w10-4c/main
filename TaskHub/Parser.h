#ifndef PASER_H_
#define PASER_H_

#include <iostream>
#include <string>
using namespace std;

class Textbody
{
public:
	//vector<string> Textbody;
	Textbody();
	Textbody(string input);
	~Textbody();
	Textbody(string Textbody, string input);
	string ToString();
	string get_TextbodyName();
	void UpdateTextbody(string input);
	void MarkDone();
	void MarkUndone();
	void checkInputValidation();
	
private:
	string _TextbodyName;
	string _TextbodyType;
	string _startTime;
	string _endTime;
	string _deadlineTime;
	string _scheduledDate;
	string _deadlineDate;
	string _status;
};

#endif