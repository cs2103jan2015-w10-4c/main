#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandClearTest{

	TEST_CLASS(CommandClearTest){

	public:

		TEST_METHOD(TestClear){
			//test case 1
			CommandClear::clearTask ("all");
			std::string expectedOutput = "All messages have been clear";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);

			//test case 2
			CommandAdd::addOperation("cs meeting");
			CommandAdd::addOperation("cs meeting and tutorial");
			CommandClear::clearTask ("1-2");
			std::string expectedOutput2 = "Message with index from 1 to 2 have been clear";
			std::string actualOutput2 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput2, actualOutput2);

			//test case 3
			CommandAdd::addOperation("cs meeting");
			CommandAdd::addOperation("cs meeting and tutorial");
			CommandClear::clearTask ("1-4");
			std::string expectedOutput3 = "Invalid Task Index";
			std::string actualOutput3 = Logic::messageDisplayed;
			CommandClear::clearTask("all");
			Assert::AreEqual(expectedOutput3, actualOutput3);

		}

	};

}