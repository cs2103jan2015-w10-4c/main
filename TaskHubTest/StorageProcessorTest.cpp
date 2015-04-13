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
			Assert::IsNotNull(&testResult1);
			Assert::AreEqual(testResult1, expectedResult1);

			//test case 2	with quotation marks
			std::string testString("\"abc.txt\"");
			std::string testResult2 = test->processFileDirectory(testString);
			Assert::AreEqual(testResult2, expectedResult1);
			Assert::AreEqual(testResult1, testResult2);
			Assert::AreNotEqual(testString, testResult2);

			delete test;
		}

		// The following test method tests the correctness of the function, isValidFileFormat(),
		// which utilises other private functions such as isMinRequiredNameLength() and
		// isTextFileFormat.
		// The feasibility and the robustness of this function would suggest the private functions 
		// are also working correctly.
		TEST_METHOD(TestIsValidFileFormat){
			StorageProcessor* test = new StorageProcessor();

			//test case 1	empty file name
			std::string file1("");
			Assert::IsFalse(test->isValidFileFormat(file1));

			//test case 2:	file name too short
			std::string file2("a");
			Assert::IsFalse(test->isValidFileFormat(file2));

			//test case 3:	no extension in file name
			std::string file3("thisfilename");
			Assert::IsFalse(test->isValidFileFormat(file3));

			//test case 4:	invalid extension 
			std::string file4("storage.exe");
			Assert::IsFalse(test->isValidFileFormat(file4));

			//test case 5:	lower boundary case
			std::string file5("a.txt");
			Assert::IsTrue(test->isValidFileFormat(file5));

			//test case 6:	file path directory
			std::string file6("C:\\Desktop\\MapleStory\\save.txt");
			Assert::IsTrue(test->isValidFileFormat(file6));

			delete test;
		}

		TEST_METHOD(TestConvertToUpperCase){
			StorageProcessor* test = new StorageProcessor();

			//test case 1:	lower to upper case
			char result1 = test->convertToUpperCase('a');
			Assert::AreEqual(result1, 'A');
			Assert::AreNotEqual(result1, 'a');

			//test case 2:	upper case remains untouched
			char result2 = test->convertToUpperCase('A');
			Assert::AreEqual(result2, 'A');
			Assert::AreEqual(result1, result2);

			//test case 3:	non-alphabetical char remains untouched
			char result3 = test->convertToUpperCase('2');
			Assert::AreEqual(result3, '2');
			char result4 = test->convertToUpperCase('?');
			Assert::AreEqual(result4, '?');

			delete test;
		}
	};
}