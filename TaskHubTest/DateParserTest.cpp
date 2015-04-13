#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskHubTest
{
	TEST_CLASS(DateParserTest)
	{
	public:
		
		TEST_METHOD(Test)
		{
			//test case 1
			
			string input =  "-from 13:00 -to 14:00 12/4 @tuown";
			DateParser temp(input);

			
		}

	};
}