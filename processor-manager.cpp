#include "processor-manager.h"
using namespace std; 


ProcessorManager::ProcessorManager(int dm_processors, int lru_processors){
	number_of_processors = dm_processors + lru_processors; 
	is_buffer_init = false; 
	buffer_hole = -1; 
	is_hole = false;
	
	processors = new Bus*[number_of_processors]; 
	buffer = new int*[number_of_processors]; 
	collector = new MOESIData(number_of_processors); 	
	processor_bus = new Bus(collector);

	for(int i = 0; i < number_of_processors; i++){
		if(i < dm_processors){
			processors[i] = new DirectMapProcessor(); 
			collector->label(processors[i], DirectMapping, ("p" + to_string(i)));	
		}
		else{
			processors[i] = new LeastRecentlyUsedProcessor(); 	
			collector->label(processors[i], LRU, ("p" + to_string(i)));	
		}		
		
		processor_bus->initProcessor(processors[i]); 
		buffer[i] = new int(-1);

	}

}

string** ProcessorManager::commandToProcessor(string** commands){
	if(!(is_buffer_init)){
		is_buffer_init = initBuffer(buffer, commands); 
	}
	
	if((is_hole) && (nullptr != commands[buffer_hole])){
		buffer[buffer_hole] = new int(getCycleFromCommand(*commands[buffer_hole]));
		is_hole = false; 
	}

	int prediction = nextCommand(buffer); 
	if(-1 == prediction){
		initBuffer(buffer, commands);
		if(-1 == nextCommand(buffer)){
			return nullptr; 
		}
		commandToProcessor(commands);
	}
	if(checkCommand(*buffer[prediction], *commands[prediction])){
		int action = getActionFromCommand(*commands[prediction]); 
		string address = getAddressFromCommand(*commands[prediction]);
		int index = 0; 
		
		BUS_SIGNAL proc_signal = processors[prediction]->execute(action, *buffer[prediction], index,  address);
		if(processor_bus->SIGNALALL(proc_signal, index, *buffer[prediction], processors[prediction])){
			
			int* delete_this_number = buffer[prediction];
			string* delete_this_string = commands[prediction];

			delete delete_this_number; 
			delete delete_this_string;
			commands[prediction] = nullptr; 
			buffer[prediction] = nullptr; 

			buffer_hole = prediction; 
			is_hole = true; 

			return commands; 
		}
	}
	else{
		is_buffer_init = false; 
		return commandToProcessor(commands); 
	}
	return nullptr; 
}

void ProcessorManager::printCollectedData(){
	collector->print(reinterpret_cast<void**>(processors)); 
}

string ProcessorManager::trim(const string s){
	return rtrim(ltrim(s)); 
}

int ProcessorManager::getCycleFromCommand(string command){
	string cycle_substring = command.substr(0, command.find(' ')); 
	
	return stoi(cycle_substring); 
}

int ProcessorManager::getActionFromCommand(string command){
	int remove_cycle = command.find(' '); 
	command = command.substr(remove_cycle + 1, command.length());
	command = ltrim(command); 

	return stoi(command.substr(0, command.find(' ')));
}

string ProcessorManager::getAddressFromCommand(string command){
	for(int i = 0; i < 2; i++){
		int remove = command.find(' '); 
		command = command.substr(remove + 1, command.length());
		command = ltrim(command); 
	}
	
	return trim(command); 
}

int ProcessorManager::nextCommand(int** cycle_buffer){
	int next_command = -1; 
	bool empty_buffer = true; 
       	for(int i = 0; i < number_of_processors; i++){
		if(nullptr != cycle_buffer[i]){
			next_command = i; 
			empty_buffer = false; 
			break; 
		}
	}	
	
	if(empty_buffer){
		return next_command; 
	}

	for(int i = next_command; i < number_of_processors; i++){
		if((nullptr != cycle_buffer[i]) && (*cycle_buffer[i] < *cycle_buffer[next_command])){
			next_command = i; 
		}
	}

	return next_command; 
}

bool ProcessorManager::checkCommand(int cycle, string command){
	return (cycle == getCycleFromCommand(command)); 
}

bool ProcessorManager::initBuffer(int** cycle_buffer, string** commands){
	for(int i = 0; i < number_of_processors; i++){
		if(nullptr != commands[i]){
			*cycle_buffer[i] = getCycleFromCommand(*commands[i]); 
		}
		else{
			cycle_buffer[i] = nullptr; 
		}
	}
	return true; 
}

string ProcessorManager::ltrim(const string s){
	size_t start = s.find_first_not_of(" \n\r\t\f\v");
	return (start == string::npos) ? "" : s.substr(start);
}	

string ProcessorManager::rtrim(const string s){
	 size_t end = s.find_last_not_of(" \n\r\t\f\v");
	     return (end == string::npos) ? "" : s.substr(0, end + 1);
}	
