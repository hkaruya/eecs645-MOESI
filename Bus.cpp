#include "Bus.h"
using namespace std; 

Bus::Bus(Bus* processor, ...){	
	va_list variables;
	va_start(variables, processor);

	all_processors = new Bus*[NUMBER_OF_PROCESSORS]; 
	all_processors[0] = processor; 
	
	for(int i = 1; i < NUMBER_OF_PROCESSORS; i++){
		all_processors[i] = dynamic_cast<Bus*>(va_arg(variables, Bus*)); 
	}
	va_end(variables); 
}

Bus::Bus(){
	all_processors = nullptr; 
}

bool Bus::SIGNALALL(BUS_SIGNAL signal, int index){
	for(int i=0; i < NUMBER_OF_PROCESSORS; i++){
		if(nullptr != all_processors[i]){
			if(!(all_processors[i]->RECIEVESIGNAL(signal, index))){
				return false; 
			}	
		}
	}

	return true; 
}

BUS_SIGNAL Bus::execute(int action, string address){
	return None; 
}

bool Bus::RECIEVESIGNAL(BUS_SIGNAL signal, int index){
	return false; 
}
