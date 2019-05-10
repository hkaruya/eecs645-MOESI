#include "dm-processor.h"
using namespace std; 

DirectMapProcessor::DirectMapProcessor(){
	for(int i = 0; i < LINE_SIZE; i++){
		cache_state[i] = INVALID; 
	}
}

BUS_SIGNAL DirectMapProcessor::execute(int action, int cycle, string address){
	string tag = "";
	int index = -1;
	getTagAndIndex(tag, index, Bus::hexToBinary(address)); 
	if((READ == action) && (isDirtyWriteback(tag, processor_cache.read(index, cycle), cache_state[index]))){
		//return Dirty_Writeback
	}
	
	processor_cache.write(tag, index, cycle); 
	return MOESI::processorBasedProtocol(cache_state[index], action); 
}

BUS_SIGNAL DirectMapProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	//cout<<"signal_recieved"<<endl; 
	return MOESI::busBasedProtocol(signal, cache_state[index]); 	
}

bool DirectMapProcessor::FLUSH(Bus* source, int index, int cycle){
	processor_cache.write(source->getTag(index, cycle), index, cycle);
	return true; 
}

string DirectMapProcessor::getTag(int index, int cycle){
	return processor_cache.read(index, cycle); 
}
