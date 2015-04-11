#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandUpdateTest{

	TEST_CLASS(CommandUpdateTest){

	public:

		TEST_METHOD(TestUpdate){
			CommandAdd::addMessage ("cs meeting -from 13:00 -to 18:00 11/4");
			CommandUpdate::updateMessage("1 -from 14:00");
			std::string expectedOutput = "Task: cs meeting [ 11/4 14:00 - 18:00 ]  progressing is updated";
			std::string actualOutput = Logic::messageDisplayed;
			CommandClear::clearTask("all");
			Assert::AreEqual(expectedOutput, actualOutput);

			CommandAdd::addMessage ("cs meeting -from 13:00 -to 18:00 11/4");
			CommandUpdate::updateMessage("1 -from 14:00 -to 15:00");
			std::string expectedOutput2 = "Task: cs meeting [ 11/4 14:00 - 15:00 ]  progressing is updated";
			std::string actualOutput2 = Logic::messageDisplayed;
			CommandClear::clearTask("all");
			Assert::AreEqual(expectedOutput2, actualOutput2);

			CommandAdd::addMessage ("cs meeting -from 13:00 -to 18:00 11/4");
			CommandUpdate::updateMessage("1 -from 14:00 -to 15:00 12/4");
			std::string expectedOutput3 = "Task: cs meeting [ 12/4 14:00 - 15:00 ]  progressing is updated";
			std::string actualOutput3 = Logic::messageDisplayed;
			CommandClear::clearTask("all");
			Assert::AreEqual(expectedOutput3, actualOutput3);

			CommandAdd::addMessage ("cs meeting -from 13:00 -to 18:00 11/4");
			CommandUpdate::updateMessage("1 cs lecture -from 14:00 -to 15:00 12/4");
			std::string expectedOutput4 = "Task:  cs lecture  [ 12/4 14:00 - 15:00 ]  progressing is updated";
			std::string actualOutput4 = Logic::messageDisplayed;
			CommandClear::clearTask("all");
			Assert::AreEqual(expectedOutput4, actualOutput4);

			CommandAdd::addMessage ("cs meeting -from 13:00 -to 18:00 11/4");
			CommandUpdate::updateMessage("1 cs lecture");
			std::string expectedOutput5 = "Task:  cs lecture [ 11/4 13:00 - 18:00 ]  progressing is updated";
			std::string actualOutput5 = Logic::messageDisplayed;
			CommandClear::clearTask("all");
			Assert::AreEqual(expectedOutput5, actualOutput5);
		}

	};

}