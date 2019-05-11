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
	return None; 
}

string LeastRecentlyUsedProcessor::getTag(int index, int cycle){

}

BUS_SIGNAL LeastRecentlyUsedProcessor::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	return None; 
}

bool LeastRecentlyUsedProcessor::FLUSH(Bus* source, int index, int cycle){

}
