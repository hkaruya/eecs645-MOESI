#include "dm-processor.h"
using namespace std; 

DirectMapProcessor::DirectMapProcessor(){
	for(int i = 0; i < LINE_SIZE; i++){
		cache_state[i] = INVALID; 
	}
}

BUS_SIGNAL DirectMapProcessor::execute(int action, int cycle, int& index, string address){
	string tag = "";
	getTagAndIndex(tag, index, Bus::hexToBinary(address)); 
	if((READ == action) && (isDirtyWriteback(tag, processor_cache.read(index, cycle), cache_state[index]))){
		if(nullptr != this->collector) this->collector->dirtyWriteback(this); 
	}
	
	processor_cache.write(tag, index, cycle);

	State before = cache_state[index]; 
	BUS_SIGNAL return_signal = MOESI::processorBasedProtocol(cache_state[index], action); 
	State after = cache_state[index]; 

	if(nullptr != this->collector) this->collector->stateShift(this, before, after); 

	return return_signal; 
}

BUS_SIGNAL DirectMapProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	State before = cache_state[index]; 
	BUS_SIGNAL return_signal = MOESI::busBasedProtocol(signal, cache_state[index]);
	State after = cache_state[index]; 

	if(nullptr != this->collector) this->collector->stateShift(this, before, after);

	return return_signal; 	
}

bool DirectMapProcessor::FLUSH(Bus* source, int index, int cycle){
	if(nullptr != this->collector) this->collector->stateShift(this, INVALID, SHARED); 

	cache_state[index] = SHARED; 
	processor_cache.write(source->getTag(index, cycle), index, cycle);
	return true; 
}

string DirectMapProcessor::getTag(int index, int cycle){
	return processor_cache.read(index, cycle); 
}
