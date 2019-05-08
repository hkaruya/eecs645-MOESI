#include "dm-processor.h"
using namespace std; 

DirectMapProcessor::DirectMapProcessor(){
	for(int i = 0; i < LINE_SIZE; i++){
		cache_state[i] = INVALID; 
	}
}

BUS_SIGNAL DirectMapProcessor::execute(int action, string address){
	return None; 
}
bool DirectMapProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	return true; 
}
