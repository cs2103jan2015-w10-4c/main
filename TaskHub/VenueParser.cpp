//author: A0115399W

#include "VenueParser.h"
#include <string>

const string MARK_AT = "@";

VenueParser::VenueParser(void){
}


VenueParser::VenueParser(string input){
	_venue = input.substr(input.find(MARK_AT));
}

string VenueParser::getVenue(){
	return _venue;
}