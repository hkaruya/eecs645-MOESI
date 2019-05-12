using namespace std; 
#include <iostream> 
#include "front-end.h"

int main(int argc, char** argv){
	cout<<"Hello World !!!"<<endl;	
	
	string* processor_commands = new string[argc - 1];
	for(int i = 0; i < (argc - 1); i++){
		processor_commands[i] = argv[i+1]; 
	}

	FrontEnd user_interface((argc - 1), processor_commands); 
       user_interface.run(); 	
	

	delete[] processor_commands; 
	
	//int NUMBER_OF_PROCESSORS = 4;
	//ProcessorManager pm(NUMBER_OF_PROCESSORS, 0); 
	//string** test_commands = new string*[NUMBER_OF_PROCESSORS];
	//test_commands[0] = new string("323 1 0x195d5910");
	//test_commands[1] = new string("270 1 0x195d5af0"); 
	//test_commands[2] = new string("259 1 0x195d5cd0");
	//test_commands[3] = new string("152 1 0x195d5eb0");
	//while(nullptr != pm.commandToProcessor(test_commands));
	//string tag = "";
	//int index = -1;  
	//Bus::getTagAndIndex(tag, index, Bus::hexToBinary("0x195d5910"));  
	//cout<<tag<<endl; 
	//cout<<index<<endl; 
	//0x195d5910
return(0);
}
