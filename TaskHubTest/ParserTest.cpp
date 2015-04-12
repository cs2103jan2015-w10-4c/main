#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest{

	TEST_CLASS(ParserTest){
	public:


		TEST_METHOD(TestgetTaskName){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "Write code";
			std::string realOutput = task.getTaskName();
			Assert::AreEqual(realOutput, expectedOutput);
		}
		TEST_METHOD(TestgetTaskType){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "timed";
			std::string realOutput = task.getTaskType();
			Assert::AreEqual(realOutput, expectedOutput);
		}
		TEST_METHOD(TestgetStartTime){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12:00";
			std::string realOutput = task.getStartTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestgetEndTime){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "19:00";
			std::string realOutput = task.getEndTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestgetScheduledDate){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12/04";
			std::string realOutput = task.getScheduledDate();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestgetScheduledDateReverse){
			std::string testInput = "Write code -from 12:00 -to 19:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "04/12";
			std::string realOutput = task.getScheduledDateReverse();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestgetDeadlineDate){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12/04";
			std::string realOutput = task.getDeadlineDate();
			Assert::AreEqual(expectedOutput,realOutput);
		}
			TEST_METHOD(TestgetDeadlineTime){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "12:00";
			std::string realOutput = task.getDeadlineTime();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestgetStatus){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "progressing";
			std::string realOutput = task.getStatus();
			Assert::AreEqual(realOutput, expectedOutput);
		}
//			TEST_METHOD(TestgetDeadlineTime){
			//std::string testInput = "Write code -by 12:00 12/04";
			//Task task(testInput);
			//std::string expectedOutput = "12:00";
			//std::string realOutput = task.getDeadlineTime();
			//Assert::AreEqual(realOutput, expectedOutput);
		//}
			TEST_METHOD(TestgetVenue){
			std::string testInput = "Write code @NUS";
			Task task(testInput);
			std::string expectedOutput = "@NUS";
			std::string realOutput = task.getVenue();
			Assert::AreEqual(realOutput, expectedOutput);
		}
			TEST_METHOD(TestgetIntegerDay){
			std::string testInput = "Write code -by 12:00 12/04";
			Task task(testInput);
			std::string expectedOutput = "";
			std::string realOutput = task.getVenue();
			Assert::AreEqual(realOutput, expectedOutput);
		}
	};

}