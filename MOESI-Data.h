#ifndef MOESI_DATA_H 
#define MOESI_DATA_H
#include <string>
#include <unordered_map>
#include "data-collect.h"
#include "protocol.h"
#include "cache.h"

using namespace std; 

class MOESIData{
	public:
		MOESIData(int processor_count);
		void print(void** processors);

		bool label(void* processor, string processor_alias); 
		bool cacheToCache(void* source, void* destination); 
		bool cacheToMemory(void* source); 
		bool dirtyWriteback(void* processor); 
		bool stateShift(void* processor, State prev_state, State curr_state); 
	private:	
		bool invalidation(void* processor, State prev_state); 
		static void printString(string& value); 

		DataCollect<string> cache_transfers;
		DataCollect<string> mem_transfers; 
	       	DataCollect<string> dirty_writeback;
			
		DataCollect<string>** invalidations; 
		DataCollect<string>** states_census; 

		unordered_map<void*, string> aliases; 
		unordered_map<string, int> assignments; 

		unsigned int number_of_processors; 

		//aliases.find(key) == aliases.end()
};
#endif
