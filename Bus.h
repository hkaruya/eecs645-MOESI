#ifndef BUS_H
#define BUS_H 
#include <stdarg.h>

const int MAX_PROC_SIZE = 32; 

using namespace std; 

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
	None
}BUS_SIGNAL;

class Bus{
	public:
		Bus(Bus* processor, ...); 
		bool SIGNALALL(BUS_SIGNAL signal); 
	protected:
		Bus(); 
		virtual void RECIEVESIGNAL(BUS_SIGNAL signal) = 0; 
	private:
		Bus** all_processors; 
		int number_of_processors;
};
#endif
