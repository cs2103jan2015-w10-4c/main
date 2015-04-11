//author: A0115399W

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

