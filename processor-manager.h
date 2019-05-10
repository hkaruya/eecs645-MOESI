#ifndef PROCESSOR_MANAGER_H 
#define PROCESSOR_MANAGER_H 
#include "dm-processor.h"
#include "lru-processor.h"
//#include "MOESI-data.h"
#include <string>

using namespace std; 

class ProcessorManager{
	public: 
		ProcessorManager(int dm_processors, int lru_processors); 
		string** commandToProcessor(string** commands); 
		//PRINTSTATS
	private:
		int getCycleFromCommand(string command); 
		int getActionFromCommand(string command); 
		string getAddressFromCommand(string command); 

		int nextCommand(int** cycle_buffer); 

		Bus processor_bus; 
		Bus** processors; 
		int** buffer; 
		int number_of_processors;
		//DataCollector
}; 
#endif
