#ifndef BUS_H
#define BUS_H 
#include <stdarg.h>
#include <string>

const int NUMBER_OF_PROCESSORS = 4; 

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
		bool SIGNALALL(BUS_SIGNAL signal, int index); 
		virtual BUS_SIGNAL execute(int action, string address); 
	protected:
		Bus(); 
		virtual bool RECIEVESIGNAL(BUS_SIGNAL signal, int index); 
	private:
		Bus** all_processors; 
};
#endif
