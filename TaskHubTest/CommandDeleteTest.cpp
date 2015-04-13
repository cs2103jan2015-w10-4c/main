//@author A0115365J

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandDeleteTest{

	TEST_CLASS(CommandDeleteTest){

	public:

		TEST_METHOD(TestDelete){
			//test case 1
			CommandDelete::deleteMessage("1");
			std::string expectedOutput = "Invalid index";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);

			//test case 2
			CommandAdd::addOperation("cs meeting");
			CommandDelete::deleteMessage("1");
			std::string expectedOutput2 = "Message \" cs meeting  progressing \" is deleted";
			std::string actualOutput2 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput2, actualOutput2);

			//test case 3
			CommandDelete::deleteMessage("1000000000");
			std::string expectedOutput3 = "Invalid index";
			std::string actualOutput3 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput3, actualOutput3);

		}

	};

}