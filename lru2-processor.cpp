#include "lru2-processor.h"
using namespace std;

LeastRecentlyUsedProcessor::LeastRecentlyUsedProcessor(){
	for(int i = 0; i < NUMBER_OF_CACHES; i++){
		for(int j = 0; j < LINE_SIZE; j++){
			cache_state[i][j] = INVALID; 
		}
	}
}

BUS_SIGNAL LeastRecentlyUsedProcessor::execute(int action, string address){
	return None; 
}

bool LeastRecentlyUsedProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	return true; 
}
