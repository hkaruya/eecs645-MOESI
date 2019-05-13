#include "front-end.h"

using namespace std; 


FrontEnd::FrontEnd(int processor_count){
	welcome(); 

	size = processor_count; 

	readers = new ifstream*[processor_count];
	command_buffer = new string*[processor_count];
	for(int i = 0; i < processor_count; i++){
		command_buffer[i] = nullptr;
	       	readers[i] = new ifstream; 	
	}

	cout<<"Type (1): Direct-Map Single Cache Processor"<<endl;
	cout<<"Type (2): Least Recently Used Double Cache Processor"<<endl;
	/*you have the choice between two types of processors
	 * (1) dm single cache processor
	 * (2) lru double cache processor
	 */

	int dm_processors, lru_processors; 

	while((dm_processors + lru_processors) != processor_count){
		dm_processors = lru_processors = 0; 

		cout<<"[POOL: "<<processor_count<<"] ";
		cout<<"How many of type (1) processor(s): ";
		cin>>dm_processors;
		if((processor_count - dm_processors) != 0){
			cout<<"[POOL: "<<(processor_count - dm_processors)<<"] ";
			cout<<"How many of type (2) processor(s): "; 
			cin>>lru_processors;
			while(cin.fail()){
				cin.clear();
				cin.ignore(4, '\n');
				cout<<"\tIt appears you entered an invalid input, try again"<<endl; 
				cout<<"\t> ";
				cin>>lru_processors;
			}
		} 
	}
	cout<<endl; 

	manager = new ProcessorManager(dm_processors, lru_processors);
	
	cout<<"Enter filename for files containing processor commands"<<endl; 
	int counter = 1;	
	string file_name; 

	while(processor_count+1 != counter){
		cout<<"processor ["<<counter<<"] : ";
		cin>>file_name;

		readers[counter - 1]->open(file_name);
		while(readers[counter - 1]->fail()){
			cout<<"\tINVALID FILE NAME [FILE DOES NOT EXIST]"<<endl; 
			cout<<"\tEnter again: "; 
			cin>>file_name; 

			readers[counter - 1]->open(file_name); 
		}
		counter++;
	}

}

FrontEnd::FrontEnd(int processor_count, string* files){
	welcome(); 

	size = processor_count; 

	readers = new ifstream*[processor_count];
	command_buffer = new string*[processor_count];
	for(int i = 0; i < processor_count; i++){
		command_buffer[i] = nullptr;
	       	readers[i] = new ifstream; 
		readers[i]->open(files[i]); 	
	}
	cout<<"Type (1): Direct-Map Single Cache Processor"<<endl;
	cout<<"Type (2): Least Recently Used Double Cache Processor"<<endl;
	/*you have the choice between two types of processors
	 * (1) dm single cache processor
	 * (2) lru double cache processor
	 */

	int dm_processors, lru_processors; 
	
	while((dm_processors + lru_processors) != processor_count){
		dm_processors = lru_processors = 0; 

		cout<<"[POOL: "<<processor_count<<"] ";
		cout<<"How many of type (1) processor(s): ";
		cin>>dm_processors;
		while(cin.fail()){
			cin.clear();
			cin.ignore(4, '\n');
			cout<<"\tIt appears you entered an invalid input, try again"<<endl; 
			cout<<"\t> ";
			cin>>dm_processors; 
		}

		if((processor_count - dm_processors) != 0){
			cout<<"[POOL: "<<(processor_count - dm_processors)<<"] ";
			cout<<"How many of type (2) processor(s): "; 
			cin>>lru_processors;
			while(cin.fail()){
				cin.clear();
				cin.ignore(4, '\n');
				cout<<"\tIt appears you entered an invalid input, try again"<<endl; 
				cout<<"\t> ";
				cin>>lru_processors;
			}
		}
	}
	
	cout<<endl; 

	manager = new ProcessorManager(dm_processors, lru_processors);
}

FrontEnd::~FrontEnd(){
	delete manager;

	for(int i = 0; i < size; i++){
		delete readers[i]; 
		delete command_buffer[i];
	}

	delete[] readers; 
	delete[] command_buffer;
}

void FrontEnd::run(){
	if(!(initBuffer()))return; 
	while(nullptr != manager->commandToProcessor(command_buffer))initBuffer(); 

	printCollectedData(); 
}

void FrontEnd::welcome(){
	cout<<"~WELCOME TO MY CACHE SIMULATOR~"<<endl;
	cout<<"[By: HERBERT ARUYA]"<<endl; 
}

void FrontEnd::printCollectedData(){
	manager->printCollectedData();
}

bool FrontEnd::initBuffer(){
	for(int i = 0; i < size; i++){
		if((nullptr == command_buffer[i]) && (!(readers[i]->eof()))){
			command_buffer[i] = new string(""); 
			
			getline(*readers[i], *command_buffer[i]);
			if("" == *command_buffer[i]){
				string* delete_this = command_buffer[i]; 
				delete delete_this; 

				command_buffer[i] = nullptr; 
			}
		}
	}
	return true; 
}
