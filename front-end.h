#ifndef FRONT_END_H
#define FRONT_END_H
#include <fstream>
#include <iostream>
#include "processor-manager.h"
//#include "MOESI-data.h"

using namespace std; 

class FrontEnd{
	public:
		FrontEnd(int processor_count);
		FrontEnd(int processor_count, string* files); 
		~FrontEnd();
		void run(); 
	private:
		void welcome(); 
		void printCollectedData(); 
		bool initBuffer(); 

		string** command_buffer; 
		ifstream** readers;
		ProcessorManager* manager; 
		int size; 
		//MOESIData collector; 
};		
#endif
