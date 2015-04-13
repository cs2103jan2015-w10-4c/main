//@author A0115399W
//**********************************************************
//                      class VenueParser
//     this class will receive input from parser class, and its job is to extract out veune in form of string
//     and return the values back to parser class.
//
//******************************************************************
#ifndef VENUEPARSER_H
#define VENUEPARSER_H
#include <string>
using namespace std;
class VenueParser
{
public:
	VenueParser(void);
	VenueParser(string input);
	string getVenue();
private:
	string _venue;
};
#endif

