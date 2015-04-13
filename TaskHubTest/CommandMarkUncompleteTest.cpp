//@author A0115365J

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandMarkUncompleteTest{

	TEST_CLASS(CommandMarkUncompleteTest){

	public:

		TEST_METHOD(TestMarkUncomplete){

			//test case 1
			markingMessageUncomplete::markMessageUncompleted("1");
			std::string expectedOutput = "Invalid index";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);

			//test case 2
			CommandAdd::addOperation("cs meeting");
			markingMessageUncomplete::markMessageUncompleted("1");
			std::string expectedOutput2 = "Task \" cs meeting  uncompleted \" is marked";
			std::string actualOutput2 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput2, actualOutput2);
			CommandDelete::deleteMessage("1");

		}

	};

}