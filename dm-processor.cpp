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
	if((READ == action) && (isDirtyWriteback(this, 0, tag, processor_cache.read(index, cycle), cache_state[index]))){
		if(nullptr != this->collector) this->collector->dirtyWriteback(this); 
	}
	
	processor_cache.write(tag, index, cycle);

	State before = cache_state[index]; 
	BUS_SIGNAL return_signal = MOESI::processorBasedProtocol(cache_state[index], action); 
	State after = cache_state[index]; 

	if(nullptr != this->collector) this->collector->stateShift(this, 0, before, after); 

	return return_signal; 
}

BUS_SIGNAL DirectMapProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index, string tag){
	if(tag != processor_cache.read(index, -1)) return None; 
	
	State before = cache_state[index]; 
	BUS_SIGNAL return_signal = MOESI::busBasedProtocol(signal, cache_state[index]);
	State after = cache_state[index]; 
	
	if((Flush == return_signal) || (FlushX == return_signal)) this->flush_value = tag;

	if(nullptr != this->collector) this->collector->stateShift(this, 0, before, after);

	return return_signal; 	
}

bool DirectMapProcessor::FLUSH(Bus* source, int index, int cycle){
	if(nullptr != this->collector) this->collector->stateShift(this, 0, cache_state[index], SHARED); 

	cache_state[index] = SHARED; 
	processor_cache.write(source->getFlush(), index, cycle);
	return true; 
}

string DirectMapProcessor::getTag(int index){
	return processor_cache.read(index, -1); 
}
