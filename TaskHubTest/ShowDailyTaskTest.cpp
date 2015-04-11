#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandShowDailyTaskTest{

	TEST_CLASS(CommandShowDailyTaskTest){

public:

	TEST_METHOD(TestShow){
		CommandAdd::addOperation("cs meeting");
		ShowDailyTask::showDayTask("all");
		std::string expectedOutput = "Nothing found on that day";
		std::string actualOutput = ShowDailyTask::showDayTask("all");
		Assert::AreEqual(expectedOutput, actualOutput);
		CommandClear::clearTask("all");

		CommandAdd::addOperation("cs meeting -from 14:00 -to 15:00 5/5");
		ShowDailyTask::showDayTask("5/5");
		std::string expectedOutput2 = "Task is shown";//"cs meeting [ 5/5 14:00 -to 15:00 ]  progressing";
		std::string actualOutput2 = ShowDailyTask::showDayTask("5/5");
		Assert::AreEqual(expectedOutput2, actualOutput2);
		CommandClear::clearTask("all");

		CommandAdd::addOperation("cs meeting -from 14:00 -to 15:00 5/5");
		ShowDailyTask::showDayTask("5/5");
		std::string expectedOutput3 = "1. cs meeting [ 5/5 14:00 - 15:00 ]  progressing\n";
		std::string actualOutput3 = ShowDailyTask::showDayTask("5/5");
		std::vector <string> actualString = ShowDailyTask::messageDisplayed;
		Assert::AreEqual(expectedOutput3, actualString[0]);
		CommandClear::clearTask("all");

	}

	};

}