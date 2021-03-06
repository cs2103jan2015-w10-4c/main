//@author:A0115793Y
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest{

	TEST_CLASS(CommandDetailTest){

	public:
		
		TEST_METHOD(TestDetailMessage) {
			//test case 1
			std::string testSentence1 = "0";
			std::string testResult1 = CommandDetail::detailMessage(testSentence1);
			std::string actualResult1("");
			Assert::AreEqual(actualResult1, testResult1);
			//test case 2
			std::string testSentence2 = "1dkjsdf jdfks";
			std::string testResult2 = CommandDetail::detailMessage(testSentence2);
			std::string actualResult2("");
			Assert::AreEqual(actualResult2, testResult2);
		}
		TEST_METHOD(TestCheckInputValidation) {
			//test case 1
			std::string testSentence1 = "0";
			Assert::IsTrue(CommandDetail::checkInputValidation(testSentence1));
			//test case 2
			std::string testSentence2 = "1dkjsdf jdfks";
			Assert::IsFalse(CommandDetail::checkInputValidation(testSentence2));
		}

	};
}