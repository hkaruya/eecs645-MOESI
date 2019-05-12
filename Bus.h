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
		//Initializes processor(s) bus, setting collector to nullptr (collects data)
		Bus(); 

		//Initilizes processor(s) bus, setting collector to new_collector
		//@param: new_collector
		Bus(MOESIData* new_collector);

		virtual ~Bus();

		//Signals all processors using this bus
		//@param: signal 
		//@param: index, indiciates which index in cache to notify
		//@param: cycle, cycle in which signalling is happening
		//@param: caller, used in case of flush; helps know which processor to flush to
		//@return: true once signalling is performed properly, false if error
		bool SIGNALALL(BUS_SIGNAL signal, int index, int cycle, Bus* caller); 

		//Initializes processor to this bus so signalling can happen properly(calling and recieving)
		//@param: processor, processor to add to bus
		//@return: true once initialized, false once processor cap is reached
		bool initProcessor(Bus* processor); 

		//Executes given address and returns bus signal if necessary
		//@param: action, read or write
		//@param: cycle, cycle in which execution happens
		//@param: index
		//@param: address, hexidecimal address
		virtual BUS_SIGNAL execute(int action, int cycle, int& index, string address); 

		//Returns the most recently used processors tag at given index
		//@param: index
		//@return: tag at given index
	       	virtual string getTag(int index); 

		//Returns value to flush, used in cases of Flush or FlushX bus signal
		string getFlush() const; 

		//Static function that turns a string of hex to a string of binary
		//@param: hex_number
		//@return: binary string
		static string hexToBinary(string hex_number); 
	protected:
		//execute helpter function that partitions binary string to three parts, offset, index and tag
		//@param: tag
		//@param: index
		//@param: binary
		//@return: true once partitioned, false if error occurs
		bool getTagAndIndex(string& tag, int& index, string binary); 

		//Checks to see if case is dirty writeback
		//@param: processor, processor in question
		//@param: cache_index
		//@param: new_tag, new tag from most recent command
		//@param: current_tag, current tag in cache 
		//@param: current_state, current state of processor
		//@return: true if dirty writecback occurs
		bool isDirtyWriteback(Bus* processor, int cache_index, string new_tag, string current_tag, State& current_state);

		//Used in signal all, processor specific function that recieves signal generated by another process connected in bus
		//@param: signal
		//@param: index, place within cache where signal is to be recieved
		//@param: tag, tag in cache coming from processor that signal
		//@return: BUS_SIGNAL generated by original signal (Flush or FlushX)
		virtual BUS_SIGNAL RECIEVESIGNAL(BUS_SIGNAL signal, int index, string tag); 

		//Used in execute, processor specific function that handles flushing between processors
		//@param: source, source of flush
		//@param: index, index in chache where flush is happening
		//@param: cycle
		//@return: true once flushed
		virtual bool FLUSH(Bus* source, int index, int cycle);

		MOESIData* collector;
		string flush_value; 
	private:
		Bus** all_processors; 
		int is_initialized; 
};
#endif
