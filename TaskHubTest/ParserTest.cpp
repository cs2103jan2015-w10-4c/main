#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest{

	TEST_CLASS(ParserTest){
	public:


		TEST_METHOD(TestGetTaskName){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "Write code";
			std::string realOutput = task.getTaskName();
			Assert::AreEqual(realOutput, expectedOutput);
		}
		TEST_METHOD(TestGetTaskType){
			//deadline tasks
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "deadline";
			std::string realOutput = task.getTaskType();
			Assert::AreEqual(realOutput, expectedOutput);

			//floating tasks
			std::string testInput2 = "CS Project";
			Task task2(testInput2);
			std::string expectedOutput2 = "floating";
			std::string realOutput2 = task2.getTaskType();
			Assert::AreEqual(realOutput2, expectedOutput2);
		}
		TEST_METHOD(TestGetStartTime){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12:00";
			std::string realOutput = task.getStartTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestGetEndTime){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "19:00";
			std::string realOutput = task.getEndTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestGetScheduledDate){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12/04";
			std::string realOutput = task.getScheduledDate();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestGetScheduledDateReverse){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "04/12";
			std::string realOutput = task.getScheduledDateReverse();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestGetDeadlineDate){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12/04";
			std::string realOutput = task.getDeadlineDate();
			Assert::AreEqual(expectedOutput,realOutput);
		}
			TEST_METHOD(TestGetDeadlineTime){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12:00";
			std::string realOutput = task.getDeadlineTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestGetStatus){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "progressing";
			std::string realOutput = task.getStatus();
			Assert::AreEqual(realOutput, expectedOutput);
		}
//			TEST_METHOD(TestGetDeadlineTime){
			//std::string testInput = "Write code -by 12:00 12/04";
			//Task task(testInput);
			//std::string expectedOutput = "12:00";
			//std::string realOutput = task.getDeadlineTime();
			//Assert::AreEqual(realOutput, expectedOutput);
		//}
			TEST_METHOD(TestGetVenue){
			std::string testInput = "Write code @NUS";
			Task task(testInput);
			std::string expectedOutput = "@NUS";
			std::string realOutput = task.getVenue();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestGetIntegerDay){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "";
			std::string realOutput = task.getVenue();
			Assert::AreEqual(realOutput, expectedOutput);
		}
	};

}