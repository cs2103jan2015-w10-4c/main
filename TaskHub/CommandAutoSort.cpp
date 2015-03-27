#include "CommandAutoSort.h"

void CommandAutoSort::autoSort () {
	
	vector<Task> temporary=Logic::history.getVectorTextStorage();

	for (unsigned int i=0;i<Logic::history.getVectorTextStorage().size() - 1; i++) {
		temporary[i];//all forms are in int// get month //get date//get hour//get minute

		//sort month
		//sort date
		//sort hour
		//sort minute
		temporary[i+1];
	}



	Logic::history.setVectorTextStorage(temporary);
	return;

}