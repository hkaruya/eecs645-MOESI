using namespace std; 
#include <iostream> 
#include "dm-processor.h"

int main(int argc, char** argv){
	int NUMBER_OF_PROCESSORS = 4;
	DirectMapProcessor p[NUMBER_OF_PROCESSORS];
	Bus* processor_bus = new Bus();	
	int i = 0; 
	while(processor_bus->initProcessor(&p[i])){
		i++; 
		if(!(i < NUMBER_OF_PROCESSORS)){
			break; 
		}
	}
	processor_bus->SIGNALALL(None, 0, 0, &p[0]); 
	cout<<"Hello World !!!"<<endl;	

	//string tag = "";
	//int index = -1;  
	//Bus::getTagAndIndex(tag, index, Bus::hexToBinary("0x195d5910"));  

	//cout<<tag<<endl; 
	//cout<<index<<endl; 
	
	//0x195d5910
return(0);
}
