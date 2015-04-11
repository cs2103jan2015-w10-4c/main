#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TaskHubTest
{
	TEST_CLASS(CommandClashTest)
	{
	public:
		
		TEST_METHOD(TestisClash)
		{
			//test case 1
			CommandAdd::addMessage("meeting -from 13:00 -to 14:00 12/4");
			string testSentence1 = "-from 13:00 -to 14:00";
			string actualOutput1 = CommandClash::clash(testSentence1);
			string expectedOutput1 = "-from 13:00 -to 14:00 does not clash with existing tasks";
			Assert::AreEqual(expectedOutput1,actualOutput1);
			//test case 2
			CommandAdd::addMessage("meeting -from 13:00 -to 14:00 12/4");
			string testSentence2 = "-from 13:00 -to 14:00 12/4";
			string actualOutput2 = CommandClash::clash(testSentence2);
			string expectedOutput2 = "-from 13:00 -to 14:00 12/4 clashes with existing tasks";
			Assert::AreEqual(expectedOutput2,actualOutput2); 
		}
		TEST_METHOD(TestgetDayTasks)
		{
			//test case 1
			CommandAdd::addMessage("meeting -from 13:00 -to 14:00 12/4");
			CommandAdd::addMessage("cs meeting -from 13:00 -to 15:00 13/4");
			CommandAdd::addMessage("ie meeting -from 15:00 -to 18:00 12/4");
			vector<Task> temporary1 = StorageDatabase::taskHistory.getVectorTextStorage();
			int day1 = 12;
			int month1 = 4;
			vector<Task> actualOutput1 = CommandClash::getDayTasks(temporary1,day1,month1);
			vector<Task> expectedOutput1;
			Task temp1("meeting -from 13:00 -to 14:00 12/4");
			Task temp2("ie meeting -from 15:00 -to 18:00 12/4");
			expectedOutput1.push_back(temp1);
			expectedOutput1.push_back(temp2);
			for(unsigned int i=0;i<actualOutput1.size();i++) {
				Assert::AreEqual(expectedOutput1[i].ToString(),actualOutput1[i].ToString());
			}
			
			//test case 2
			CommandAdd::addMessage("meeting -from 13:00 -to 14:00 12/4");
			CommandAdd::addMessage("cs meeting -from 13:00 -to 15:00 13/4");
			CommandAdd::addMessage("ie meeting -from 15:00 -to 18:00 12/4");
			vector<Task> temporary2 = StorageDatabase::taskHistory.getVectorTextStorage();
			int day2 = 14;
			int month2 = 4;
			vector<Task> actualOutput2 = CommandClash::getDayTasks(temporary2,day2,month2);
			Assert::IsTrue(actualOutput2.empty());

			CommandClear::clearTask("all");
		}


	};
}