#ifndef THCOMMAND_H_
#define THCOMMAND_H_

#include <string>
using namespace std;


//this function is to encasulate user input in a standard format

class THCommand {
public:

	THCommand();

	void setCommand(THUtility::CommandType);
	void setDescription(string);
	void setStartingDate(string);
	void setStartingTime(string);
	void setEndingDate(string);
	void setEndingTime(string);

	bool haveCommand();
	bool haveDetail();
	bool haveStartingDate();
	bool haveStartingTime();
	bool haveEndingDate();
	bool haveEndingTime();

	THUtility::CommandType getCommand();
	string getDescription();
	string getStartingDate();
	string getStartingTime();
	string getEndingDate();
	string getEndingTime();

	void clearCommand();

private:

	THUtility::CommandType _commandType;
	bool _haveCommand;
	string _description;
	string _StartingDate;
	string _StartingTime;
	string _EndingDate;
	string _EndingTime;
};

#endif