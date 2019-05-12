#ifndef PROCESSOR_MANAGER_H 
#define PROCESSOR_MANAGER_H 
#include "dm-processor.h"
#include "lru-processor.h"
#include "MOESI-Data.h"
#include <string>

using namespace std; 

class ProcessorManager{
	public:
	       	//Initializes processor manager
		//This class facilitates data collection and makes sure processor/processor bus runs smoothly
		//@param: dm_processors,number of direct map processors
		//@param: lru_processors, number of lru processors	
		ProcessorManager(int dm_processors, int lru_processors);

		//Sends command to correct processor to execute, assures commands are executed chronologically
		//@param: commands, array of commands ranging from 0 to number_of_processors
		//@return: nullptr when no more commands are left to run, other wise valid string array with
				//nullptr holding place of command that was just executed
		string** commandToProcessor(string** commands); 

		//Prints data collected by data collector
		void printCollectedData();

		//Static function that trims white wpace from the beginning and end of string
		static string trim(const string s); 
	private:
		//commandToProcessor helper function that partitions command and returns part specifying cycle
		//@param: command
		//@return: cycle of command that is given
		int getCycleFromCommand(string command);

		//commandToProcessor helpter function that partitions command and returns part pertaining to action to perfom
		//@param: command
		//@return: action specified by given command (0 or 1)	
		int getActionFromCommand(string command); 

		//commandToProcessor helper function that partitions command and returns hexidecimal address part of command
		//@param: command
		//@return: hexidecimal as a string
		string getAddressFromCommand(string command); 
		
		//commandToProcessor helper function that notifies which command to execute next
		//@param: buffer, array of ints that are the cycles of current command
		//@return: index of which command in string array used to execute
		int nextCommand(int** cycle_buffer); 

		//Checks if given cycle matches the cycle given in command
		//@param: cycle
		//@param: command
		//@return: true if they match, false otherwise
		bool checkCommand(int cycle, string command); 

		//Populates buffer with the cycle partition of each command
		//@param: cycle_buffer, array to populate
		//@return: true once finished, false if not valid command
		bool initBuffer(int** cycle_buffer, string** commands); 

		//Trim helper function, trims left hand side of string
		static string ltrim(const string s); 

		//Trim helper function, trims right hand side of string
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
