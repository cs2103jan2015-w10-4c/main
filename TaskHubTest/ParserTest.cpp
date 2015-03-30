#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest{

	TEST_CLASS(ParserTest){
	public:

		//test on funtionality of VenueParser class
		TEST_METHOD(TestVenueParser){
			std::string testInput = "Write code @NUS";
			VenueParser parseVenue(testInput);
			std::string expectedOutput = "NUS";
			std::string realOutput = parseVenue.getVenue();
			Assert::AreEqual(realOutput, expectedOutput);

		// Boundary case: empty venue

		}
	};

}