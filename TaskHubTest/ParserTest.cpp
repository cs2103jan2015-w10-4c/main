#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest{

	TEST_CLASS(ParserTest){
	public:


		TEST_METHOD(TestGetTaskName){
			//test case 1: deadline task
			std::string testInput1 = "Write code -by 12:00 12/04";
			Task task1(testInput1);
			std::string expectedOutput1 = "Write code";
			std::string realOutput1 = task1.getTaskName();
			Assert::AreEqual(realOutput1, expectedOutput1);

			//test case 2: floating task
			std::string testInput2 = "Write code";
			Task task2(testInput2);
			std::string expectedOutput2 = "Write code";
			std::string realOutput2 = task2.getTaskName();
			Assert::AreEqual(realOutput2, expectedOutput2);
		}

		TEST_METHOD(TestGetTaskType){
			//test case 1: deadline task
			std::string testInput1 = "Write code -by 12:00 12/04";
			Task task1(testInput1);
			std::string expectedOutput1 = "deadline";
			std::string realOutput1 = task1.getTaskType();
			Assert::AreEqual(realOutput1, expectedOutput1);

			//test case 2: timed task
			std::string testInput2 = "Write code -from 12:00 -to 00:00 12/04";
			Task task2(testInput2);
			std::string expectedOutput2 = "timed";
			std::string realOutput2 = task2.getTaskType();
			Assert::AreEqual(realOutput2, expectedOutput2);

			//test case 3: floating task
			std::string testInput3 = "Write code";
			Task task3(testInput3);
			std::string expectedOutput3 = "floating";
			std::string realOutput3 = task3.getTaskType();
			Assert::AreEqual(realOutput3, expectedOutput3);
		}


		TEST_METHOD(TestGetStartTime){
			//test case 1: lower boundary case
			std::string testInput = "Write code -from 00:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "00:00";
			std::string realOutput = task.getStartTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}

			TEST_METHOD(TestGetEndTime){
			//test case 1: upper boundary case
			std::string testInput = "Write code -from 12:00 -to 23:59 12/04";
			Task task(testInput);
			std::string expectedOutput = "23:59";
			std::string realOutput = task.getEndTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}

			TEST_METHOD(TestGetScheduledDate){
			//test case 1: lower boundary case
			std::string testInput1 = "Write code -from 12:00 -to 19:00 01/01";
			Task task1(testInput1);
			std::string expectedOutput1 = "01/01";
			std::string realOutput1 = task1.getScheduledDate();
			Assert::AreEqual(realOutput1, expectedOutput1);

			//test case 2: upper boundary case
			std::string testInput2 = "Write code -from 12:00 -to 19:00 31/12";
			Task task2(testInput2);
			std::string expectedOutput2 = "19:00";
			std::string realOutput2 = task2.getEndTime();
			Assert::AreEqual(realOutput2, expectedOutput2);
		}

			TEST_METHOD(TestGetScheduledDateReverse){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "04/12";
			std::string realOutput = task.getScheduledDateReverse();
			Assert::AreEqual(realOutput, expectedOutput);
			}

			TEST_METHOD(TestGetDeadlineDate){
			//test case 1: lower boundary
			std::string testInput1 = "Write code -by 12:00 01/01";
			Task task1(testInput1);
			std::string expectedOutput1 = "01/01";
			std::string realOutput1 = task1.getDeadlineDate();
			Assert::AreEqual(expectedOutput1,realOutput1);

			//test case 2: upper boundary
			std::string testInput2 = "Write code -by 12:00 31/12";
			Task task2(testInput2);
			std::string expectedOutput2 = "31/12";
			std::string realOutput2 = task2.getDeadlineDate();
			Assert::AreEqual(expectedOutput2, realOutput2);
		}

			TEST_METHOD(TestGetDeadlineTime){
			//test case 1: lower boundary
			std::string testInput1 = "Write code -by 00:00 12/04";
			Task task1(testInput1);
			std::string expectedOutput1 = "00:00";
			std::string realOutput1 = task1.getDeadlineTime();
			Assert::AreEqual(realOutput1, expectedOutput1);

			//test case 2: upper boundary
			std::string testInput2 = "Write code -by 23:59 12/04";
			Task task2(testInput2);
			std::string expectedOutput2 = "23:59";
			std::string realOutput2 = task2.getDeadlineTime();
			Assert::AreEqual(realOutput2, expectedOutput2);
		}

			TEST_METHOD(TestGetStatus){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "progressing";
			std::string realOutput = task.getStatus();
			Assert::AreEqual(realOutput, expectedOutput);
		}


			TEST_METHOD(TestGetVenue){
			//test case 1: floating task
			std::string testInput1 = "Write code @NUS";
			Task task1(testInput1);
			std::string expectedOutput1 = "@NUS";
			std::string realOutput1 = task1.getVenue();
			Assert::AreEqual(realOutput1, expectedOutput1);

			//test case 2: timed task
			std::string testInput2 = "Write code -from 12:00 -to 19:00 12/04 @NUS";
			Task task2(testInput2);
			std::string expectedOutput2 = "@NUS";
			std::string realOutput2 = task2.getVenue();
			Assert::AreEqual(realOutput2, expectedOutput2);

			//test case 3: deadline task
			std::string testInput3 = "Write code -by 12:00 12/04 @NUS";
			Task task3(testInput3);
			std::string expectedOutput3 = "@NUS";
			std::string realOutput3 = task3.getVenue();
			Assert::AreEqual(realOutput3, expectedOutput3);
		}

			TEST_METHOD(TestGetIntegerDay){
			//test case 1: deadline task
			std::string testInput1 = "Write code -by 12:00 12/04";
			Task task1(testInput1);
			int expectedOutput1 = 12;
			int realOutput1 = task1.getIntegerDay();
			Assert::AreEqual(realOutput1, expectedOutput1);

			//test case 2: timed task
			std::string testInput2 = "Write code -from 12:00 -to 15:00 12/04";
			Task task2(testInput2);
			int expectedOutput2 = 12;
			int realOutput2 = task2.getIntegerDay();
			Assert::AreEqual(realOutput2, expectedOutput2);
		}
	};

}