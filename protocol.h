#ifndef PROTOCOL_H
#define PROTOCOL_H

#define READ 0
#define WRITE 1

using namespace std; 

typedef enum {
	MODIFIED,
	OWNER, 
	EXCLUSIVE, 
	SHARED, 
	INVALID
}State; 

typedef enum {
	BusRd, 
	BusRdX, 
	BusUpgr, 
	Flush,
	FlushX,
	None
}BUS_SIGNAL;


//INTERFACE CLASS USED TO ABSTRACT PROTOCAL
class Protocol{
	public:
		virtual BUS_SIGNAL processorBasedProtocol(State& current_state, int action) = 0; 
		virtual BUS_SIGNAL busBasedProtocol(BUS_SIGNAL signal, State& current_state) = 0; 
};
#endif
