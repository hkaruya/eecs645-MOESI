using namespace std; 
#include <iostream> 
#include "dm-processor.h"

int main(int argc, char** argv){
	DirectMapProcessor p1;
       	DirectMapProcessor p2;
	DirectMapProcessor p3;
	DirectMapProcessor p4; 

	Bus* processor_bus = new Bus(&p1, &p2, &p3, &p4, nullptr);  	
	cout<<"Hello World !!!"<<endl;	
	cout<<LINE_SIZE<<endl; 
return(0);
}
