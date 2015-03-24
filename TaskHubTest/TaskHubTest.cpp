#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest
{		
	TEST_CLASS(UITest){
	public:
		
		TEST_METHOD(UITestMethod1){
			// TODO: Your test code here
		}

	};

	TEST_CLASS(LogicTest){
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
	};

	TEST_CLASS(ParserTest){
	public:

		TEST_METHOD(TestVenueParser){
			std::string testInput = "Write code @NUS";
			VenueParser parseVenue(testInput);
			std::string expectedOutput = "NUS";
			std::string realOutput = parseVenue.getVenue();
			Assert::AreEqual(realOutput, expectedOutput);
		}
	};

	TEST_CLASS(StorageTest){
	public:

		TEST_METHOD(StorageTestMethod1){

		}

	};
}