//@author A0115365J

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandSearchTest{

	TEST_CLASS(CommandSearchTest){

	public:

		TEST_METHOD(TestSearch){

			CommandAdd::addMessage ("cs meeting -from 13:00 -to 14:00 11/4");
			CommandSearch::searchMessage("cs");
			std::string expectedOutput = "Message is shown";
			std::string expectedOutput2 = "Message is shown";
			std::string expectedOutput3 = "Message is shown";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);
			CommandSearch::searchMessage("cs meeting");
			std::string actualOutput2 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput2, actualOutput);
			CommandSearch::searchMessage("CS MEETING");
			std::string actualOutput3 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput3, actualOutput);
			CommandClear::clearTask("all");
			
			CommandAdd::addMessage ("WHAT");
			CommandSearch::searchMessage("cs");
			std::string expectedOutput4 = "Cannot find message";
			std::string expectedOutput5 = "Message is shown";
			std::string expectedOutput6 = "Message is shown";
			std::string actualOutput4 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput4, actualOutput4);
			CommandSearch::searchMessage("WHAT");
			std::string actualOutput5 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput5, actualOutput);
			CommandSearch::searchMessage("what");
			std::string actualOutput6 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput6, actualOutput);
			CommandClear::clearTask("all");

			CommandSearch::searchMessage("cs meeting");
			std::string expectedOutput7 = "The file is empty";
			std::string actualOutput7 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput7, actualOutput7);
		}

	};

}