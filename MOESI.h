#ifndef MOESI_H
#define MOESI_H
#include "protocol.h"

using namespace std; 

class MOESI{
	public: 
	       	//Protocol handler, processes processor based actions and returns signal corresponding
		//@param: current_state, current state of processor
		//@param: action, action taken by processor (READ or WRITE)	
		static BUS_SIGNAL processorBasedProtocol(State& current_state, int action);  

		//Protocol handlaer, covers bus based signals and effects to processor state
		//@param: signal, signal recieved by processor
		//@param: current_state, state of processor
		static BUS_SIGNAL busBasedProtocol(BUS_SIGNAL signal, State& current_state); 
};
#endif
