#include "VenueParser.h"
#include <string>

VenueParser::VenueParser(void){
}


VenueParser::VenueParser(string input){
	_venue = input.substr(input.find("@"), input.size());
}

string VenueParser::getVenue(){
	return _venue;
}