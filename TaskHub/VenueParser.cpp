//@author: A0115399W
#include "VenueParser.h"
#include <string>

VenueParser::VenueParser(void){
}


VenueParser::VenueParser(string input){
	_venue = input.substr(input.find("@"));
}

string VenueParser::getVenue(){
	return _venue;
}