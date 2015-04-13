//@author: A0115399W
#include "VenueParser.h"
#include <string>
const string AT = "@";

VenueParser::VenueParser(void){
}


VenueParser::VenueParser(string input){
	_venue = input.substr(input.find(AT));
}

string VenueParser::getVenue(){
	return _venue;
}