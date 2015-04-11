#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandAddTest{

	TEST_CLASS(CommandAddTest){

	public:

			TEST_METHOD(TestAdd){
				//test case 1
				CommandAdd::addMessage ("");
				std::string expectedOutput1 = "invalid input";
				std::string actualOutput1 = Logic::messageDisplayed;
				Assert::AreEqual(expectedOutput1, actualOutput1);

				//test case 2
				CommandAdd::addMessage ("add");
				std::string expectedOutput2 = "invalid input";
				std::string actualOutput2 = Logic::messageDisplayed;
				Assert::AreEqual(expectedOutput2, actualOutput2);
				
				//test case 3
				CommandAdd::addMessage ("                                                             ");
				std::string expectedOutput3 = "invalid input";
				std::string actualOutput3 = Logic::messageDisplayed;
				Assert::AreEqual(expectedOutput3, actualOutput3);

				//test case 4
				CommandAdd::addMessage ("cs meeting -from 13:00 -to 14:00 11/4");
				std::string expectedOutput4 = "Task: \" cs meeting [ 11/4 13:00 - 14:00 ]  progressing \" added";
				std::string actualOutput4 = Logic::messageDisplayed;
				CommandClear::clearTask("all");
				Assert::AreEqual(expectedOutput4, actualOutput4);
				
			}

	};

}