#include "cache.h"
using namespace std; 

Cache::Cache(){
	for(int i = 0; i < LINE_SIZE; i++){
		tag_array[i] = ""; 
		age_array[i] = nullptr; 
	}
}

Cache::~Cache(){
	for(int i = 0; i < LINE_SIZE; i ++){
		//delete age_array[i]; 
	}
}

void Cache::write(string address_tag, int index, int cycle){
	if((0 > index) || (LINE_SIZE >= index)){
		//TODO throw cache exception
	}

	tag_array[index] = address_tag; 
	if(nullptr == age_array[index]){
		age_array[index] = new int(cycle); 
	}
	else{
		*(age_array[index])= cycle;  
	}

}

string Cache::read(int index, int cycle){	
	if(nullptr == age_array[index]){
		//TODO throw cache exception
	}

	*(age_array[index]) = cycle;
	return tag_array[index]; 
}

int Cache::lastAccessCycle(int index){
	int* cycle = age_array[index]; 
	if(nullptr != cycle){
		return *(cycle); 	
	}
	return -1; 
}
