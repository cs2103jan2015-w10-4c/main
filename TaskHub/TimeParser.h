#ifndef TIMEPARSER_H
#define TIMEPARSER_H
#include <string>
using namespace std;

class TimeParser{

public:
	TimeParser();
	TimeParser(string input);
	string getStartTime();
	string getEndTime();
<<<<<<< HEAD
	int getStartHour();
	int getStartMinute();
	int getEndHour();
	int getEndMinute();
private:
	string _startTime;
	string _endTime;
	int _startHour;
	int _startMinute;
	int _endHour;
	int _endMinute;
=======
	int getHour();
	int getMinute();
private:
	string _startTime;
	string _endTime;
	int _hour;
	int _minute;
>>>>>>> 406445856a424c95f96b866652307badb6ccb5b3
};
#endif
