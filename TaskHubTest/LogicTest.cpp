#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest{		

	TEST_CLASS(HistoryTest){
    public:

		TEST_METHOD(TestGetFirstWord){
			//test case 1
			std::string testSentence1 = "cs2103 is difficult";
			std::string testResult1 = Logic::getFirstWord(testSentence1);
			std::string actualResult1("cs2103");
			Assert::AreEqual(actualResult1, testResult1);

			//test case 2 : empty string
			std::string testSentence2 = "";
			std::string testResult2 = Logic::getFirstWord(testSentence2);
			std::string actualResult2("");
			Assert::AreEqual(actualResult2, testResult2);
		}

		TEST_METHOD(TestRemoveFirstWord){
			//test case 1
			std::string testSentence1("project is due");
			std::string testResult1 = Logic::removeFirstWord(testSentence1);
			std::string actualResult1("is due");
			Assert::AreEqual(testResult1, actualResult1);
			
			//test case 2 : empty string
			std::string testSentence2("project is due");
			std::string testResult2 = Logic::removeFirstWord(testSentence2);
			std::string actualResult2("is due");
			Assert::AreEqual(testResult2, actualResult2);
		}

		TEST_METHOD(TestLastChangedIndex){
			History* test = new History();

			test->setLastChangedTaskIndex(1);
			int testResult = test->getLastChangedTaskIndex();
			Assert::AreEqual(testResult, 0);

			delete test;
		}

		TEST_METHOD(TestLastCommandType){
			History* test = new History();

			// test case 1: previous action taken is the addition of a new task.
			test->setLastCommandType("add");
			std::string expectedResult("add");
			std::string actualResult = test->getLastCommandType();
			Assert::AreEqual(expectedResult, actualResult);

			delete test;
		}
	};

}