#include "lru-processor.h"
using namespace std;

LeastRecentlyUsedProcessor::LeastRecentlyUsedProcessor(){
	for(int i = 0; i < LRU_NUMBER_OF_CACHES; i++){
		for(int j = 0; j < LINE_SIZE; j++){
			cache_state[i][j] = INVALID; 
		}
	}
}

BUS_SIGNAL LeastRecentlyUsedProcessor::execute(int action, int cycle, int& index, string address){
	string tag = "";
	int cache_index = -1; 
	getTagAndIndex(tag, index, Bus::hexToBinary(address));

	if(READ == action){
		bool cache_read = false;
		for(int i = 0; i < LRU_NUMBER_OF_CACHES; i++){
			string current_tag = processor_cache[i].read(index, -1); 
			if(current_tag == tag){
				cache_index = i; 
				cache_read = true; 
				break; 
			}
		}

		if(!cache_read){
			cache_index = getLRU(index); 
			if(isDirtyWriteback(this, cache_index, tag, processor_cache[cache_index].read(index, -1), cache_state[cache_index][index])) this->collector->dirtyWriteback(this); 
		}
	}

	if(WRITE == action){
		cache_index = getLRU(index); 
	}
	
	processor_cache[cache_index].write(tag, index, cycle); 

	State before = cache_state[cache_index][index]; 
	BUS_SIGNAL return_signal = MOESI::processorBasedProtocol(cache_state[cache_index][index], action);
	State after = cache_state[cache_index][index]; 

	if(nullptr != this->collector) this->collector->stateShift(this, cache_index, before, after); 
	
	return return_signal; 
}

string LeastRecentlyUsedProcessor::getTag(int index){
	return processor_cache[getMRU(index)].read(index, -1); 
}

BUS_SIGNAL LeastRecentlyUsedProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index, string tag){
	for(int i = 0; i < LRU_NUMBER_OF_CACHES; i++){
		if(tag == processor_cache[i].read(index, -1)){ 

			State before = cache_state[i][index];
			BUS_SIGNAL return_signal = MOESI::busBasedProtocol(signal, cache_state[i][index]);
			State after = cache_state[i][index]; 

			if((Flush == return_signal) || (FlushX == return_signal)) this->flush_value = tag; 	
		
			if(nullptr != this->collector) this->collector->stateShift(this, i, before, after); 

			return return_signal; 	
		}
	}
	
	return None;	
}

bool LeastRecentlyUsedProcessor::FLUSH(Bus* source, int index, int cycle){
	int most_recent_cache = getMRU(index); 
	if(nullptr != this->collector) this->collector->stateShift(this, most_recent_cache, cache_state[most_recent_cache][index], SHARED); 

	cache_state[most_recent_cache][index] = SHARED; 
	processor_cache[most_recent_cache].write(source->getFlush(), index, cycle); 

	return true; 
}

int LeastRecentlyUsedProcessor::getLRU(int index){
	int cache_index = 0; 
	int index_age = processor_cache[cache_index].lastAccessCycle(index);

	for(int i = 1; i < LRU_NUMBER_OF_CACHES; i++){
		int prospective_index_age = processor_cache[i].lastAccessCycle(index);
		if(prospective_index_age < index_age){
			cache_index = i; 
			index_age = prospective_index_age; 
		}
	}

	return cache_index; 
}

int LeastRecentlyUsedProcessor::getMRU(int index){
	int cache_index = 0; 
	int index_age = processor_cache[cache_index].lastAccessCycle(index);

	for(int i = 1; i < LRU_NUMBER_OF_CACHES; i++){
		int prospective_index_age = processor_cache[i].lastAccessCycle(index);
		if(prospective_index_age > index_age){
			cache_index = i; 
			index_age = prospective_index_age; 
		}
	}

	return cache_index; 
}
