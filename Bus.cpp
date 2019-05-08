#include "Bus.h"
using namespace std; 

Bus::Bus(Bus* processor, ...){
	number_of_processors = 0;
	Bus** temp = new Bus*[MAX_PROC_SIZE]; 
	va_list variables;
	va_start(variables, processor);

	while(processor){
		temp[number_of_processors] = va_arg(variables, Bus*); 
		number_of_processors++; 
	}
	
	va_end(variables); 

	all_processors = new Bus*[number_of_processors];
	for(int i = 0; i < number_of_processors; i++){
		all_processors[i] = temp[i]; 
	}

}

Bus::Bus(){
	all_processors = nullptr; 
	number_of_processors = 0; 
}

bool Bus::SIGNALALL(BUS_SIGNAL signal){
	if(0 == number_of_processors){
		return false; 
	}

	for(int i=0; i < number_of_processors; i++){
		all_processors[i]->RECIEVESIGNAL(signal); 
	}

	return true; 
}
