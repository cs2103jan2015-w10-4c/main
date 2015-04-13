//@author:A0115793Y
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest
{
	TEST_CLASS(PaserUpdateTest)
	{
	public:
		
		TEST_METHOD(TestUpdateTask)
		{
			Task scheduledTask("meeting -from 13:00 -to 15:00 12/4 @utown");
			Task deadlineTask("meeting -by 15:00 12/4 @biz");
			Task floatingTask("meeting");
			
			//test case 1
			string input1 = "-from 13:30";
			scheduledTask.UpdateTask(input1);
			string actualOutput1 = scheduledTask.getStartTime();
			string expectedOutput1 ="13:30";
			Assert::AreEqual(actualOutput1,expectedOutput1);

			//test case 2
			string input2 = "-to 15:30";
			scheduledTask.UpdateTask(input2);
			string actualOutput2 = scheduledTask.getEndTime();
			string expectedOutput2 = "15:30";
			Assert::AreEqual(actualOutput2,expectedOutput2);

			//test case 3
			string input3 = "-from 13:30 -to 15:30";
			scheduledTask.UpdateTask(input3);
			string actualOutput3 = scheduledTask.getStartTime();
			string expectedOutput3 ="13:30";
			Assert::AreEqual(actualOutput3,expectedOutput3);

			//test case 4
			string input4 = "-from 13:30 -to 15:30";
			scheduledTask.UpdateTask(input4);
			string actualOutput4 = scheduledTask.getEndTime();
			string expectedOutput4 ="15:30";
			Assert::AreEqual(actualOutput4,expectedOutput4);

			//test case 5
			string input5 = "13/4";
			scheduledTask.UpdateTask(input5);
			string actualOutput5 = scheduledTask.getScheduledDate();
			string expectedOutput5 = "13/4";
			Assert::AreEqual(actualOutput5,expectedOutput5);

			//test case 6
			string input6 = "@computing";
			scheduledTask.UpdateTask(input6);
			string actualOutput6 = scheduledTask.getVenue();
			string expectedOutput6 = "@computing";
			Assert::AreEqual(actualOutput6,expectedOutput6);

			//test case 7
			string input7 = "2nd meeting";
			scheduledTask.UpdateTask(input7);
			string actualOutput7 = scheduledTask.getTaskName();
			string expectedOutput7 = " 2nd meeting";
			Assert::AreEqual(expectedOutput7,actualOutput7);

			//test case 8
			string input8 = "-by 13:30 13/4 @computing";
			deadlineTask.UpdateTask(input8);
			string actualOutput8 = deadlineTask.getDeadlineTime();
			string expectedOutput8 ="13:30";
			Assert::AreEqual(actualOutput8,expectedOutput8);

			//test case 9
			//string input9 = "-by 13:30 13/4 @computing";
			deadlineTask.UpdateTask(input8);
			string actualOutput9 = deadlineTask.getDeadlineDate();
			string expectedOutput9 ="13/4";
			Assert::AreEqual(actualOutput9,expectedOutput9);

			//test case 10
			deadlineTask.UpdateTask(input8);
			string actualOutput10 = deadlineTask.getVenue();
			string expectedOutput10 ="@computing";
			Assert::AreEqual(actualOutput10,expectedOutput10);

			//test case 11
			string input11 = "meeting agenda";
			floatingTask.UpdateTask(input11);
			string actualOutput11 = floatingTask.getTaskName();
			string expectedOutput11 = " meeting agenda";
			Assert::AreEqual(actualOutput11,expectedOutput11);

		}

	};
}