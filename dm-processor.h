#ifndef DM_PROCESSOR_H
#define DM_PROCESSOR_H 
#include <iostream>
#include "Bus.h"
#include "cache.h"

using namespace std; 

class DirectMapProcessor: public Bus{
	public: 
		DirectMapProcessor(); 
		BUS_SIGNAL execute(int action, string address); 
	protected: 
		bool RECIEVESIGNAL(BUS_SIGNAL signal, int index); 
	private:
		Cache processor_cache; 
		state cache_state[LINE_SIZE]; 
};
#endif
