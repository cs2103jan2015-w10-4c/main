#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandMarkDoneTest{

	TEST_CLASS(CommandMarkDoneTest){

	public:

		TEST_METHOD(TestMarkDone){
			markingDoneMessage::markMessageDone("1");
			std::string expectedOutput = "Invalid index";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);

		}

	};

}