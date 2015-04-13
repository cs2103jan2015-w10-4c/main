//@author A0111322E

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest{

	TEST_CLASS(StorageControllerTest) {
	public:
		
		TEST_METHOD(TestSetFileName){
			StorageController* test = new StorageController();
			
			//test case 1
			std::string fileName1("a.txt");
			std::string expectedResult1("a.txt");
			test->setFileName(fileName1);
			std::string testResult1 = test->getFileName();
			Assert::AreEqual(expectedResult1, testResult1);

			//test case 2:	empty string
			std::string expectedResult2("");
			test->setFileName("");
			std::string testResult2 = test->getFileName();
			Assert::AreEqual(expectedResult2, testResult2);

			//test case 3:	longer string with non numerical or alphabetical symbols
			test->setFileName("adasfd.fdfdg\\dfggdfg");
			std::string testResult3 = test->getFileName();
			std::string expectedResult3("adasfd.fdfdg\\dfggdfg");
			Assert::AreEqual(testResult3, expectedResult3);
			Assert::AreNotEqual(testResult1, expectedResult3);

			delete test;
		}

	};
}