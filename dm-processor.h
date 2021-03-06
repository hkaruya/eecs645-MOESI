#ifndef DM_PROCESSOR_H
#define DM_PROCESSOR_H 
#include <iostream>
#include "Bus.h"
#include "MOESI.h"
#include "cache.h"

using namespace std; 

class DirectMapProcessor: public Bus{
	public:	
	       	//Initializes direct-map processor	
		DirectMapProcessor(); 
		BUS_SIGNAL execute(int action, int cycle, int& index, string address); 
		string getTag(int index);
	protected: 
		BUS_SIGNAL RECIEVESIGNAL(BUS_SIGNAL signal, int index, string tag);
	       	bool FLUSH(Bus* source, int index, int cycle);	
	private:
		Cache processor_cache; 
		State cache_state[LINE_SIZE]; 
};
#endif
