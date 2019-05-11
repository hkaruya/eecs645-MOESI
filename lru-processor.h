#ifndef LRU_PROCESSOR_H
#define LRU_PROCESSOR_H
#include <iostream>
#include "Bus.h"
#include "cache.h"

const int NUMBER_OF_CACHES = 2; 

using namespace std; 
class LeastRecentlyUsedProcessor: public Bus{
	public: 
		LeastRecentlyUsedProcessor(); 
		BUS_SIGNAL execute(int action, int cycle, int& index, string address); 
		string getTag(int index, int cycle); 
	protected:
		BUS_SIGNAL RECIEVESIGNAL(BUS_SIGNAL signal, int index); 
		bool FLUSH(Bus* source, int index, int cycle); 
	private: 
		Cache processor_cache[NUMBER_OF_CACHES]; 
		State cache_state[NUMBER_OF_CACHES][LINE_SIZE]; 

};
#endif
