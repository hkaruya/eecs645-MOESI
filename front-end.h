#ifndef FRONT_END_H
#define FRONT_END_H
#include <fstream>
#include <iostream>
#include "processor-manager.h"
//#include "MOESI-data.h"

using namespace std; 

class FrontEnd{
	public:
		//Initizlizes user interface for program
		//@param: processor_count, number of processors needed
		//@post: initializes processors, user defined and asks users for filenames (used for processors)
		FrontEnd(int processor_count);
		
		//Initializes user interface for program
		//@param: processor_count, number of processors needed
		//@param: files, array with name of files to be used by processors
		FrontEnd(int processor_count, string* files); 

		//Decostructur; used to prevent memory leaks
		~FrontEnd();

		//Runs program, feeds commands given to by files in chronological order to processors
		void run(); 
	private:
		//Welcomes user to program
		void welcome(); 

		//Prints data collected by processors
		void printCollectedData(); 

		//Initialies buffer, which is string array holding commands read from files (one command at a time for each file)
		bool initBuffer(); 

		string** command_buffer; 
		ifstream** readers;
		ProcessorManager* manager; 
		int size; 
		//MOESIData collector; 
};		
#endif
