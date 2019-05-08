#ifndef DM_PROCESSOR_H
#define DM_PROCESSOR_H 
#include <iostream>
#include "Bus.h"
#include "cache.h"

using namespace std; 

class DirectMapProcessor: public Bus{
	public: 
		DirectMapProcessor(); 

	protected: 
		void RECIEVESIGNAL(BUS_SIGNAL signal); 
	private:
		Cache processor_cache; 
		state cache_states[LINE_SIZE]; 
};
#endif
