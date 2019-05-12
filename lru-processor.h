#ifndef LRU_PROCESSOR_H
#define LRU_PROCESSOR_H
#include <iostream>
#include "Bus.h"
#include "cache.h"
#include "MOESI.h"

using namespace std; 
class LeastRecentlyUsedProcessor: public Bus{
	public:	
	       	//Initilizes LRU processor	
		LeastRecentlyUsedProcessor(); 
		BUS_SIGNAL execute(int action, int cycle, int& index, string address); 
		string getTag(int index); 
	protected:
		BUS_SIGNAL RECIEVESIGNAL(BUS_SIGNAL signal, int index, string tag); 
		bool FLUSH(Bus* source, int index, int cycle); 
	private: 
		//Helper function used to get least used cache at certain index
		//@param: index
		//@return: index for least used processor
		int getLRU(int index); 

		//Helper function used to get most used cache at certain index
		//@param: index
		//@return: index for most recently used processor
		int getMRU(int index); 

		Cache processor_cache[LRU_NUMBER_OF_CACHES]; 
		State cache_state[LRU_NUMBER_OF_CACHES][LINE_SIZE]; 

};
#endif
