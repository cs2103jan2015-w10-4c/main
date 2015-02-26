#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTests
{		
	TEST_CLASS(TextBuddyTest)
	{
	public:
		TEST_METHOD(isValidInputTest) {
			Assert::IsTrue(TextBuddy::isValidInput(""));
			Assert::IsTrue(TextBuddy::isValidInput(" "));

			Assert::IsFalse(TextBuddy::isValidInput("sample text"));
		}

		TEST_METHOD(getFirstWordTest) {
			Assert::AreEqual("sample", TextBuddy::getFirstWord("sample text").c_str());
			Assert::AreEqual("sample", TextBuddy::getFirstWord("sample ").c_str());

			Assert::AreEqual("", TextBuddy::getFirstWord("").c_str());
			Assert::AreEqual("", TextBuddy::getFirstWord(" ").c_str());

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
					TextBuddy::determineCommandType("sample text"))
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
					TextBuddy::determineCommandType("sample text"))
			);


		}

		TEST_METHOD(clearAllTest) {
			const string ExpOutput = "all content deleted from heytemp123.txt";

			Assert::AreEqual(ExpOutput, TextBuddy::clearAll("heytemp123.txt"));
		}

		TEST_METHOD(addLineTest) {

			const string addInput = "hello there!";
			const string ExpOutput = "added to heytemp123.txt: \"hello there!\"";

			Assert::AreEqual(ExpOutput, TextBuddy::addLine("heytemp123.txt", addInput));
		}


		TEST_METHOD(displayAllTest) {

			const string ExpEmptyOutput = "heytemp123.txt is empty";
			const string ExpOutput = "";

			//clear file
			TextBuddy::clearAll("heytemp123.txt");
			TextBuddy::writeToFile("heytemp123.txt");

			Assert::AreEqual(ExpEmptyOutput, TextBuddy::displayAll("heytemp123.txt"));

			//set up file
			TextBuddy::addLine("heytemp123.txt", "sample text");
			TextBuddy::addLine("heytemp123.txt", "sample ");
			TextBuddy::writeToFile("heytemp123.txt");

			Assert::AreEqual(ExpOutput, TextBuddy::displayAll("heytemp123.txt"));

			//clear file
			TextBuddy::clearAll("heytemp123.txt");
			TextBuddy::writeToFile("heytemp123.txt");
		}

		TEST_METHOD(deleteLineTest) {
			const string ExpOutput = "deleted from heytemp123.txt: \"sample \"";

			//set up file
			TextBuddy::addLine("heytemp123.txt", "sample text");
			TextBuddy::addLine("heytemp123.txt", "sample ");
			TextBuddy::writeToFile("heytemp123.txt");

			Assert::AreEqual(ExpOutput, TextBuddy::deleteLine("heytemp123.txt", "2"));

			//clear file
			TextBuddy::clearAll("heytemp123.txt");
			TextBuddy::writeToFile("heytemp123.txt");
		}

		TEST_METHOD(sortAlphaTest) {

			const string ExpOutput = "all content in heytemp123.txt sorted alphabetically";

			Assert::AreEqual(ExpOutput, TextBuddy::sortLineAlphabetically("heytemp123.txt"));

		}

		TEST_METHOD(searchForWordTest) {
			const string ExpOutput1 = "found 2 result(s) in heytemp123.txt";
			const string ExpOutput2 = "found 1 result(s) in heytemp123.txt";
			const string ExpOutput3 = "found 0 result(s) in heytemp123.txt";

			//set up file
			TextBuddy::addLine("heytemp123.txt", "sample text");
			TextBuddy::addLine("heytemp123.txt", "sample ");
			TextBuddy::writeToFile("heytemp123.txt");

			Assert::AreEqual(ExpOutput1, TextBuddy::searchForWord("heytemp123.txt", "sample"));
			Assert::AreEqual(ExpOutput2, TextBuddy::searchForWord("heytemp123.txt", "sample text"));
			Assert::AreEqual(ExpOutput2, TextBuddy::searchForWord("heytemp123.txt", "text"));
			Assert::AreEqual(ExpOutput3, TextBuddy::searchForWord("heytemp123.txt", "hello"));

			//clear file
			TextBuddy::clearAll("heytemp123.txt");
			TextBuddy::writeToFile("heytemp123.txt");
		}
	};
}