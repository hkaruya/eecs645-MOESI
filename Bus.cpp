#include "Bus.h"
using namespace std; 

/*Bus::Bus(Bus* processor, ...){	
	va_list variables;
	va_start(variables, processor);

	all_processors = new Bus*[NUMBER_OF_PROCESSORS]; 
	all_processors[0] = processor; 
	
	for(int i = 1; i < NUMBER_OF_PROCESSORS; i++){
		all_processors[i] = dynamic_cast<Bus*>(va_arg(variables, Bus*)); 
	}
	va_end(variables); 
}*/

Bus::Bus(){	
	all_processors = new Bus*[MAX_NUMBER_OF_PROCESSORS]; 
	for(int i = 0; i < MAX_NUMBER_OF_PROCESSORS; i++){
		all_processors[i] = nullptr; 
	}
	collector = nullptr; 
	is_initialized = -1; 
}

Bus::Bus(MOESIData* new_collector){
	all_processors = new Bus*[MAX_NUMBER_OF_PROCESSORS]; 
	for(int i = 0; i < MAX_NUMBER_OF_PROCESSORS; i++){
		all_processors[i] = nullptr; 
	}
	collector = new_collector; 
	is_initialized = -1; 
}

bool Bus::initProcessor(Bus* processor){
	if(is_initialized == (MAX_NUMBER_OF_PROCESSORS - 1)){
		return false; 
	}

	all_processors[++is_initialized] = processor; 
	processor->collector = collector; 
	return true; 
}

bool Bus::getTagAndIndex(string& tag, int& index, string binary){
	if(BIT_LENGTH != binary.length()){
		return false; 
	}	
		
	binary = binary.substr(0, binary.length() - OFFSET_SIZE); 
	string index_string = binary.substr(binary.length() - INDEX_SIZE, binary.length()); 
	index = stoi(index_string, nullptr, 2); 
	tag = binary.substr(0, binary.length() - INDEX_SIZE); 

	return true; 
}

bool Bus::isDirtyWriteback(string new_tag, string current_tag, State& current_state){
	if(new_tag == current_tag){
		return false;
	}
	if((MODIFIED == current_state) || (OWNER == current_state)){
		current_state = INVALID; 
		return true; 
	}
	
	return false; 

}
bool Bus::SIGNALALL(BUS_SIGNAL signal, int index, int cycle, Bus* caller){
	for(int i=0; i < MAX_NUMBER_OF_PROCESSORS; i++){
		if((nullptr != all_processors[i]) && (caller != all_processors[i])){
			BUS_SIGNAL sig_return = all_processors[i]->RECIEVESIGNAL(signal, index); 
			
			if((Flush == sig_return) || (FlushX == sig_return)){
				if(FlushX == sig_return){
					if(nullptr != collector) collector->cacheToMemory(all_processors[i]); 
				}

				if(nullptr != collector) collector->cacheToCache(all_processors[i], caller); 

				caller->FLUSH(all_processors[i], index, cycle); 
				//store data point
			}
		}
	}

	return true; 
}

BUS_SIGNAL Bus::execute(int action, int cycle, int& index, string address){ return None; }

string Bus::hexToBinary(string hex_number){
	stringstream ss;
       	ss << hex << hex_number; 
	unsigned binary_number; 
	ss >> binary_number; 
	bitset<32> b(binary_number);

	return b.to_string(); 
}

BUS_SIGNAL Bus::RECIEVESIGNAL(BUS_SIGNAL signal, int index){ return None; }

bool Bus::FLUSH(Bus* source, int index, int cycle){ return false;} 

string Bus::getTag(int index, int cycle){ return ""; }
