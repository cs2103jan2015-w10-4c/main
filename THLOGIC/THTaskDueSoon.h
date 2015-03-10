

#ifndef THTaskDueSoon_H
#define THTaskDueSoon_H

//THTaskDueSoon is created by THTask to determine if a task is overdue and if its start date is today

#include <string>

class THTaskDueSoon {
public:

	THTaskDueSoon();

	bool isOverdue(string, string);
	bool isToday(string);

private:

	bool _overdue;
	bool _today;
};
#endif
