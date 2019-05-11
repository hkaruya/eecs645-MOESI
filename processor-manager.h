#ifndef PROCESSOR_MANAGER_H 
#define PROCESSOR_MANAGER_H 
#include "dm-processor.h"
#include "lru-processor.h"
#include "MOESI-Data.h"
#include <string>

using namespace std; 

class ProcessorManager{
	public: 
		ProcessorManager(int dm_processors, int lru_processors); 
		string** commandToProcessor(string** commands); 
		void printCollectedData();
		static string trim(const string s); 
		//PRINTSTATS
	private:
		int getCycleFromCommand(string command); 
		int getActionFromCommand(string command); 
		string getAddressFromCommand(string command); 

		int nextCommand(int** cycle_buffer); 
		bool checkCommand(int cycle, string command); 
		bool initBuffer(int** cycle_buffer, string** commands); 

		static string ltrim(const string s); 
		static string rtrim(const string s); 

		MOESIData* collector; 
		Bus* processor_bus; 
		Bus** processors; 
		int number_of_processors;
		
		int** buffer; 
		bool is_buffer_init; 
		int buffer_hole;
		bool is_hole; 
		//DataCollector
}; 
#endif
