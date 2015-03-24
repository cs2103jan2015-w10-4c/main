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
			std::string testSentence = "cs2103 is difficult";
			std::string testResult = Logic::getFirstWord(testSentence);
			std::string actualResult("cs2103");
			Assert::AreEqual(actualResult, testResult);
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