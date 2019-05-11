#include "MOESI.h"
using namespace std; 

BUS_SIGNAL MOESI::processorBasedProtocol(State& current_state, int action){
	if(MODIFIED == current_state){
		return None; 
	}

	if(OWNER == current_state){
		if(READ == action){
			return None; 
		}
		else if(WRITE == action){
			current_state = MODIFIED; 
			return BusUpgr; 
		}
	}

	if(EXCLUSIVE == current_state){
		if(WRITE == action){
			current_state = MODIFIED; 
		}
		return None; 
	}

	if(SHARED == current_state){
		if(WRITE == action){
			current_state = MODIFIED; 
			return BusUpgr; 
		}
		return None;
	}

	if(INVALID == current_state){
		if(READ == action){
			current_state = EXCLUSIVE; 
			return BusRd; 
		}
		else if(WRITE == action){
			current_state = MODIFIED; 
			return BusRdX;
		}

	}

	return None; 
}

BUS_SIGNAL MOESI::busBasedProtocol(BUS_SIGNAL signal, State& current_state){
	if(MODIFIED == current_state){
		if(BusRd == signal){
			current_state = OWNER; 
			return Flush; 
		}
		if(BusRdX == signal){
			current_state = INVALID; 
			return FlushX; 
		}
	}

	if(OWNER == current_state){
		if(BusRd == signal){
			return Flush;
		}
		if(BusRdX == signal){
			current_state = INVALID; 
			return FlushX; 
		}
		if(BusUpgr == signal){
			current_state = INVALID; 
			return None; 
		}
	}

	if(EXCLUSIVE == current_state){
		if(BusRd == signal){
			current_state = SHARED; 
		}
		if(BusRdX == signal){
			current_state = INVALID; 
		}

		return Flush; 
	}

	if(SHARED == current_state){
		if((BusRdX == signal ) || (BusUpgr == signal)){
			current_state = INVALID; 
		}
		return None; 
	}

	return None; 

}
