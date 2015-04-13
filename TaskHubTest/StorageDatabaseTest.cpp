//@author A0111322E

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest{

	TEST_CLASS(StorageDatabaseTest)	{

	public:
		
		TEST_METHOD(TestSetLastSavedFile){
			StorageDatabase* test = new StorageDatabase();
			
			//test case 1
			test->setLastSavedFileName("a.txt");
			std::string testResult1 = test->getLastSavedFileName();
			std::string expectedResult1("a.txt");
			Assert::AreEqual(testResult1, expectedResult1);

			//test case 2:	empty string
			test->setLastSavedFileName("");
			std::string testResult2 = test->getLastSavedFileName();
			std::string expectedResult2("");
			Assert::AreEqual(testResult2, expectedResult2);

			//test case 3	file directory
			test->setLastSavedFileName("C:\\Desktop\\MyFolder\\my.txt");
			std::string testResult3 = test->getLastSavedFileName();
			std::string expectedResult3("C:\\Desktop\\MyFolder\\my.txt");
			Assert::AreEqual(testResult3, expectedResult3);
			Assert::AreNotEqual(testResult1, expectedResult2);
			Assert::AreNotEqual(testResult3, expectedResult2);

			//test case 4	single char
			test->setLastSavedFileName("x");
			std::string testResult4 = test->getLastSavedFileName();
			std::string expectedResult4("x");
			Assert::AreEqual(testResult4, expectedResult4);

			delete test;
		}

	};
}