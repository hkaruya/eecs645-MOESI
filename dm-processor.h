#ifndef DM_PROCESSOR_H
#define DM_PROCESSOR_H 
#include <iostream>
#include "Bus.h"
#include "MOESI.h"
#include "cache.h"

using namespace std; 

class DirectMapProcessor: public Bus{
	public: 
		DirectMapProcessor(); 
		BUS_SIGNAL execute(int action, int cycle, int& index, string address); 
		string getTag(int index, int cycle);
	protected: 
		BUS_SIGNAL RECIEVESIGNAL(BUS_SIGNAL signal, int index);
	       	bool FLUSH(Bus* source, int index, int cycle);	
	private:
		Cache processor_cache; 
		State cache_state[LINE_SIZE]; 
};
#endif
