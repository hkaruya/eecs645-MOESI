#ifndef MOESI_DATA_H 
#define MOESI_DATA_H
#include <string>
#include <unordered_map>
#include "data-collect.h"
#include "protocol.h"
#include "cache.h"


typedef enum{
	DirectMapping,
	LRU
}ProcessorType;

using namespace std; 

class MOESIData{
	public:	
		//Initialize data collector for MOESI protocol based processors
		//@param: processor_count, number of processors
		MOESIData(int processor_count);

		//Print statistics of given procesors
		//@pre: processors given have to be initialized/labeled
		//@param: processors
		void print(void** processors);

		//Initialize processors by labeling them with an alias
		//@param: processor, pointer to processor
		//@param: proc_type, type of processor (DirectMap or LRU)
		//@param: processor_alias, name to give processor when printing it
		//@return: true if processor is initialied, false otherwise
		bool label(void* processor, ProcessorType proc_type, string processor_alias); 

		//Increments value for cache transfers between two caches, source and destination
		//@param: source, source of transfer
		//@param: destination, destination of transfer
		//@return: true if increment was succesful, false othewise
		bool cacheToCache(void* source, void* destination); 

		//Behaves the same as cache to cache but there is only one source register
		//Increments processor to memory counter
		//@param: source
		//@return: true once increment successful, false otherwise
		bool cacheToMemory(void* source); 

		//Increments counter when processor performs a dirty writeback
		//@param: processor, processor that does dirty writeback
		//@return: true when data is recorded, false otherwise
		bool dirtyWriteback(void* processor); 

		//When a state shifts, this function decrements the counter for prev state, and adds it to curr state
		//Adds up to LINE_SIZE
		//@param: processor, processor in which shift happens, 
		//@param: index, used if processor is of type LRU
		//@param: prev_state
		//@param: curr_state
		//@return: true once state shift is documented, false otherwise
		bool stateShift(void* processor, int index, State prev_state, State curr_state); 
	private:	
		//Initializes processor of given type, used in label funciton 
		//@param: processor
		//@return: true once finished initializing
		bool initType(void* processor); 

		//Used in state shift function, collects the data of state shift to INVALID	
		//@param: processor
		//@param:prav_state, state before becoming INVALID
		bool invalidation(void* processor, State prev_state); 

		//Static cunction used in print function
		static void printString(string& value); 

		DataCollect<string> cache_transfers;
		DataCollect<string> mem_transfers; 
	       	DataCollect<string> dirty_writeback;
			
		DataCollect<string>** invalidations; 
		DataCollect<string>*** states_census; 

		unordered_map<void*, string> aliases; 
		unordered_map<void*, ProcessorType> types; 
		unordered_map<string, int> assignments; 

		unsigned int number_of_processors; 

		//aliases.find(key) == aliases.end()
};
#endif
