#ifndef MOESI_H
#define MOESI_H
#include "protocol.h"

using namespace std; 

class MOESI{
	public:  
		static BUS_SIGNAL processorBasedProtocol(state& current_state, int action);  
		static BUS_SIGNAL busBasedProtocol(BUS_SIGNAL signal, state& current_state); 
};
#endif
