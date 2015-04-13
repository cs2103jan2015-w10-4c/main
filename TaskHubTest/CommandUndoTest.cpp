//@author A0115365J

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandUndoTest{

	TEST_CLASS(CommandUndoTest){

	public:

		TEST_METHOD(TestUndo){
			CommandAdd::addOperation("cs meeting");
			undoChange::undo();
			std::string expectedOutput = "add is undo";
			std::string actualOutput = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput, actualOutput);

			CommandAdd::addOperation("cs meeting");
			CommandDelete::deleteMessage("1");
			undoChange::undo();
			std::string expectedOutput2 = "delete is undo";
			std::string actualOutput2 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput2, actualOutput2);
			CommandDelete::deleteMessage("1");

			CommandAdd::addOperation("cs meeting");
			CommandClear::clearTask("all");
			undoChange::undo();
			std::string expectedOutput3 = "clear is undo";
			std::string actualOutput3 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput3, actualOutput3);
			CommandDelete::deleteMessage("1");

			CommandAdd::addOperation("cs meeting -from 14:00 -to 17:00 12/4");
			CommandUpdate::updateMessage("1 -from 14:30");
			undoChange::undo();
			std::string expectedOutput4 = "update is undo";
			std::string actualOutput4 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput4, actualOutput4);
			CommandDelete::deleteMessage("1");

			CommandAdd::addOperation("cs meeting -from 14:00 -to 17:00 12/4");
			markingDoneMessage::markMessageDone("1");
			undoChange::undo();
			std::string expectedOutput5 = "done is undo";
			std::string actualOutput5 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput5, actualOutput5);
			CommandDelete::deleteMessage("1");

			CommandAdd::addOperation("cs meeting -from 14:00 -to 17:00 12/4");
			markingMessageUncomplete::markMessageUncompleted("1");
			undoChange::undo();
			std::string expectedOutput6 = "uncomplete is undo";
			std::string actualOutput6 = Logic::messageDisplayed;
			Assert::AreEqual(expectedOutput6, actualOutput6);
			CommandDelete::deleteMessage("1");
		}

	};

}