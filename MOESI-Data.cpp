#include "MOESI-Data.h"
using namespace std; 


MOESIData::MOESIData(int processor_count){
	number_of_processors = processor_count;

	invalidations = new DataCollect<string>*[number_of_processors];
	states_census = new DataCollect<string>*[number_of_processors];

	for(unsigned int i = 0; i < number_of_processors; i++){
		invalidations[i] = new DataCollect<string>;
		states_census[i] = new DataCollect<string>;

		invalidations[i]->initPoint("M", 0);
		invalidations[i]->initPoint("O", 0);
		invalidations[i]->initPoint("E", 0);
		invalidations[i]->initPoint("S", 0);

		states_census[i]->initPoint("M", 0); 
		states_census[i]->initPoint("O", 0);
		states_census[i]->initPoint("E", 0);
		states_census[i]->initPoint("S", 0);
		states_census[i]->initPoint("I", LINE_SIZE);
	}
}

bool MOESIData::label(void* processor, string processor_alias){
	if(!(aliases.find(processor) == aliases.end())) return false; 
	if(aliases.size() == number_of_processors) return false; 
	
	aliases[processor] = processor_alias; 

	dirty_writeback.initPoint(processor_alias, 0); 

	assignments[processor_alias] = assignments.size() - 1; 

	return true; 
}

bool MOESIData::cacheToCache(void* source, void* destination){
	if((aliases.find(source) == aliases.end()) || (aliases.find(destination) == aliases.end())) return false; 
	
	string transfer = aliases[source] + "->" + aliases[destination];
       	if(cache_transfers.isInData(transfer)) cache_transfers.incrementPoint(transfer); 
	else cache_transfers.initPoint(transfer, 1); 

		//string flipped_transfer = aliases[destination] + "<->" + aliases[source]; 
		//if(cache_transfers.isInData(flipped_transfer)) cache_transfers.incrementPoint(flipped_transfer);
		//else cache_transfers.initPoint(transfer, 1); 
	//}

	return true; 
}

bool MOESIData::cacheToMemory(void* source){
	if(aliases.find(source) == aliases.end()) return false; 

	string transfer = aliases[source] + "->Mem"; 
	if(mem_transfers.isInData(transfer)) mem_transfers.incrementPoint(transfer);
	else mem_transfers.initPoint(transfer, 1); 

	return true; 

}
bool MOESIData::invalidation(void* processor, State prev_state){
	if(aliases.find(processor) == aliases.end()) return false; 
	
	int processor_assignment = assignments[aliases[processor]]; 
	if(MODIFIED == prev_state)invalidations[processor_assignment]->incrementPoint("M"); 
	if(OWNER == prev_state)invalidations[processor_assignment]->incrementPoint("O");	
	if(EXCLUSIVE == prev_state)invalidations[processor_assignment]->incrementPoint("E"); 
	if(SHARED == prev_state)invalidations[processor_assignment]->incrementPoint("S"); 

	return true; 
}

bool MOESIData::dirtyWriteback(void* processor){
	if(aliases.find(processor) == aliases.end()) return false; 
	
	dirty_writeback.incrementPoint(aliases[processor]); 

	return true; 
}

bool MOESIData::stateShift(void* processor, State prev_state, State curr_state){
	if(aliases.find(processor) == aliases.end()) return false; 
	
	int processor_assignment = assignments[aliases[processor]];
	if(MODIFIED == prev_state) states_census[processor_assignment]->decrementPoint("M");
	if(OWNER == prev_state) states_census[processor_assignment]->decrementPoint("O"); 
	if(EXCLUSIVE == prev_state) states_census[processor_assignment]->decrementPoint("E");  
	if(SHARED == prev_state) states_census[processor_assignment]->decrementPoint("S"); 
	if(INVALID == prev_state) states_census[processor_assignment]->decrementPoint("I"); 


	if(MODIFIED == curr_state) states_census[processor_assignment]->incrementPoint("M"); 
	if(OWNER == curr_state) states_census[processor_assignment]->incrementPoint("O"); 
	if(EXCLUSIVE == curr_state) states_census[processor_assignment]->incrementPoint("E"); 
	if(SHARED == curr_state) states_census[processor_assignment]->incrementPoint("S"); 
	if(INVALID == curr_state){
		states_census[processor_assignment]->incrementPoint("I");
		return invalidation(processor, prev_state); 
	}	

	return true; 

}

void MOESIData::print(void** processors){
	cout<<"Cache-to-Cache Transfers "<<endl; 
	cache_transfers.sortData(); 
	cache_transfers.printData(printString, false);
       	cout<<endl; 	
	
	cout<<"Cache-to-Memory Transfers"<<endl; 
       	mem_transfers.sortData(); 
	mem_transfers.printData(printString, false);
	cout<<endl;
	
	cout<<"Dirty Writeback "<<endl; 
	dirty_writeback.printData(printString, false); 
	cout<<endl;

	for(unsigned int i = 0; i < number_of_processors; i++){
		cout<<aliases[processors[i]]<<" stats: "<<endl; 

		int processor_index = assignments[aliases[processors[i]]];
		
		cout<<"Invalidations"<<endl;
		invalidations[processor_index]->printData(printString, false); 

		cout<<"Final State Configuration"<<endl; 
		states_census[processor_index]->printData(printString, false); 

		cout<<endl; 
	}
}

void MOESIData::printString(string& value){
	cout<<value; 
}
