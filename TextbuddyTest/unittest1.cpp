#include "stdafx.h"
#include "CppUnitTest.h"
#include "Textbuddy.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTests
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:	
		TEST_METHOD(isValidInputTest) {
			Assert::IsFalse(TextBuddy::isValidInput(""));
			Assert::IsFalse(TextBuddy::isValidInput(" "));

			Assert::IsTrue(TextBuddy::isValidInput("sample text Hello World!"));
		}



		TEST_METHOD(clearAllTest) {
			const string ExpectedOutput = "All message is deleted from fileName.txt";

			Assert::AreEqual(ExpectedOutput, TextBuddy::clearAll("fileName.txt"));
		}

		TEST_METHOD(addLineTest) {

			const string addInput = "Hello World!";
			const string ExpectedOutput = "Added to fileName.txt: \"Hello World!\"";

			Assert::AreEqual(ExpectedOutput, TextBuddy::addLine("fileName.txt", addInput));
		}


		TEST_METHOD(displayAllTest) {

			const string ExpEmptyOutput = "fileName.txt is empty";
			const string ExpectedOutput = "";

			//clear file
			TextBuddy::clearAll("fileName.txt");
			TextBuddy::writeToFile("fileName.txt");

			Assert::AreEqual(ExpEmptyOutput, TextBuddy::displayAll("fileName.txt"));

			//set up file
			TextBuddy::addLine("fileName.txt", "sample text Hello World!");
			TextBuddy::addLine("fileName.txt", "sample ");
			TextBuddy::writeToFile("fileName.txt");

			Assert::AreEqual(ExpectedOutput, TextBuddy::displayAll("fileName.txt"));

			//clear file
			TextBuddy::clearAll("fileName.txt");
			TextBuddy::writeToFile("fileName.txt");
		}

		TEST_METHOD(deleteLineTest) {
			const string ExpectedOutput = "Deleted from fileName.txt: \"sample \"";

			//set up file
			TextBuddy::addLine("fileName.txt", "sample text Hello World!");
			TextBuddy::addLine("fileName.txt", "sample ");
			TextBuddy::writeToFile("fileName.txt");

			Assert::AreEqual(ExpectedOutput, TextBuddy::deleteLine("fileName.txt", "2"));

			//clear file
			TextBuddy::clearAll("fileName.txt");
			TextBuddy::writeToFile("fileName.txt");
		}

		TEST_METHOD(sortTest) {

			const string ExpectedOutput = "all messages in fileName.txt are sorted alphabetically";

			Assert::AreEqual(ExpectedOutput, TextBuddy::sortLineAlphabetically("fileName.txt"));

		}


		TEST_METHOD(getFirstWordTest) {
			Assert::AreEqual("sample", TextBuddy::getFirstWord("sample text Hello World!").c_str());
			Assert::AreEqual("sample", TextBuddy::getFirstWord("sample ").c_str());

			Assert::AreEqual("", TextBuddy::getFirstWord("").c_str());
			Assert::AreEqual("", TextBuddy::getFirstWord(" ").c_str());

		}


		TEST_METHOD(searchForWordTest) {

			const string ExpectedOutput2 = "message is found at 1 in fileName.txt";
			const string ExpectedOutput3 = "message cannot be found in fileName.txt";

			//set up file
			TextBuddy::addLine("fileName.txt", "sample text Hello World!");
			TextBuddy::addLine("fileName.txt", "I am right");
			TextBuddy::writeToFile("fileName.txt");

			Assert::AreEqual(ExpectedOutput2, TextBuddy::searchForWord("fileName.txt", "sample text Hello World!"));
			Assert::AreEqual(ExpectedOutput2, TextBuddy::searchForWord("fileName.txt", "text"));
			Assert::AreEqual(ExpectedOutput3, TextBuddy::searchForWord("fileName.txt", "hello"));

			//clear file
			TextBuddy::clearAll("fileName.txt");
			TextBuddy::writeToFile("fileName.txt");
		}



		TEST_METHOD(determineCommandTypeTest) {

			const string add = "add";
			const string clear = "clear";
			const string deleteLine = "delete";
			const string display = "display";
			const string invalid = "invalid";

			Assert::AreEqual(
				add, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("Add"))
			);
			Assert::AreEqual(
				add, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("add"))
			);
			Assert::AreEqual(
				clear, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("clear"))
			);
			Assert::AreEqual(
				deleteLine, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("delete"))
			);
			Assert::AreEqual(
				display, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("display"))
			);
			Assert::AreEqual(
				invalid, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("sample text Hello World!"))
			);
			Assert::AreEqual(
				invalid,
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("sample "))
			);
			Assert::AreNotEqual(
				add, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType(" "))
			);
			Assert::AreNotEqual(
				add,
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("sample text Hello World!"))
			);


		}
	};

}