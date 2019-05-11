#ifndef BUS_H
#define BUS_H 
#include <stdarg.h>
#include <sstream>
#include <bitset>
#include <string>
#include "protocol.h"
#include "cache.h"
#include "MOESI-Data.h"

const int MAX_NUMBER_OF_PROCESSORS = 32; 

using namespace std; 

class Bus{
	public:
		Bus(); 
		Bus(MOESIData* new_collector);
		bool SIGNALALL(BUS_SIGNAL signal, int index, int cycle, Bus* caller); 
		bool initProcessor(Bus* processor); 
		virtual BUS_SIGNAL execute(int action, int cycle, int& index, string address); 
	       	virtual string getTag(int index, int cycle); 	
		static string hexToBinary(string hex_number); 
	protected:
		bool getTagAndIndex(string& tag, int& index, string binary); 
		bool isDirtyWriteback(string new_tag, string current_tag, State& current_state);
		virtual BUS_SIGNAL RECIEVESIGNAL(BUS_SIGNAL signal, int index); 
		virtual bool FLUSH(Bus* source, int index, int cycle);

		MOESIData* collector; 
	private:
		Bus** all_processors; 
		int is_initialized; 
};
#endif
