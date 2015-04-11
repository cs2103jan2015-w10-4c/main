#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandMarkDoneTest{

	TEST_CLASS(CommandMarkDoneTest){

	public:

		TEST_METHOD(TestMarkDone){
			//test case 1
			markingDoneMessage::markMessageDone("1");
			std::string expectedOutput = "Invalid index";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);

			//test case 2
			CommandAdd::addOperation("cs meeting");
			markingDoneMessage::markMessageDone("1");
			std::string expectedOutput2 = "Task \" cs meeting  done \" is completed";
			std::string actualOutput2 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput2, actualOutput2);
			CommandDelete::deleteMessage("1");

		}

	};

}