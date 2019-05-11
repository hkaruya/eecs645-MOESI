#include "lru-processor.h"
using namespace std;

LeastRecentlyUsedProcessor::LeastRecentlyUsedProcessor(){
	for(int i = 0; i < NUMBER_OF_CACHES; i++){
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
		for(int i = 0; i < NUMBER_OF_CACHES; i++){
			int old_cycle = processor_cache[i].lastAccessCycle(index);
			string current_tag = "";
		       	if(-1 != old_cycle) current_tag = processor_cache[i].read(index, old_cycle);	

			if(current_tag == tag){
				cache_read = true; 
				cache_index = i; 
				break; 
			}
		}
		if(!(cache_read)){
			cache_index = 0; 
			int index_age = processor_cache[cache_index].lastAccessCycle(index);

			for(int i = 1; i < NUMBER_OF_CACHES; i++){
				int prospective_index_age = processor_cache[i].lastAccessCycle(index);
				if(prospective_index_age < index_age){
					cache_index = i; 
					index_age = prospective_index_age; 
				}
			}
		}
	}

	if(WRITE == action){

	}

	return None; 
}

string LeastRecentlyUsedProcessor::getTag(int index, int cycle){

}

BUS_SIGNAL LeastRecentlyUsedProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	return None; 
}

bool LeastRecentlyUsedProcessor::FLUSH(Bus* source, int index, int cycle){

}
