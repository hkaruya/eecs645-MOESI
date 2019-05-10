#ifndef PROTOCOL_H
#define PROTOCOL_H

using namespace std; 

#define READ 0
#define WRITE 1

typedef enum {
	MODIFIED,
	OWNER, 
	EXCLUSIVE, 
	SHARED, 
	INVALID
}state; 

typedef enum {
	BusRd, 
	BusRdX, 
	BusUpgr, 
	Flush,
	FlushX,
	None
}BUS_SIGNAL;

class Protocol{
	public:
		virtual BUS_SIGNAL processorBasedProtocol(state& current_state, int action) = 0; 
		virtual BUS_SIGNAL busBasedProtocol(BUS_SIGNAL signal, state& current_state) = 0; 
};
#endif
