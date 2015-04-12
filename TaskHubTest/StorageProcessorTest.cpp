//@author A0111322E

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest{

	TEST_CLASS(StorageProcessorTest) {

	public:
		
		TEST_METHOD(TestProcessFileDirectory){
			StorageProcessor* test = new StorageProcessor();

			//test case 1	w/o quotation marks
			std::string testResult1 = test->processFileDirectory("abc.txt");
			std::string expectedResult1("abc.txt");
			Assert::AreEqual(testResult1, expectedResult1);

			//test case 2	with quotation marks
			std::string testString("\"abc.txt\"");
			std::string testResult2 = test->processFileDirectory("\"abc.txt\"");
			Assert::AreEqual(testResult2, expectedResult1);
			Assert::AreEqual(testResult1, testResult2);
			Assert::AreNotEqual(testString, testResult2);

			delete test;
		}

	};
}