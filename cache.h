#ifndef CACHE_H
#define CACHE_H
#include <math.h>
#include <string> 
using namespace std; 

const int MEMORY_SIZE = 16; //IN KILOBYTES
const int CACHE_LINE = 32; //IN BYTES

const int INDEX_SIZE = (int)ceil(log2((MEMORY_SIZE * pow(10, 3))/CACHE_LINE)); 
const int OFFSET_SIZE = (int)ceil(log2(CACHE_LINE)); 
const int TAG_SIZE = CACHE_LINE - INDEX_SIZE - OFFSET_SIZE; 

const int LINE_SIZE = (int)pow(2, INDEX_SIZE); 

class Cache{
	public: 
		Cache(); 
		~Cache(); 

		/*Writes address_tag to cache at index
		 * @post: address is written to tag_array
		 * @param: address_tag
		 * @param: index
		 * @param: cycle
		 */
		void write(string address_tag, int index, int cycle); 
				
		/*Gets tag at index
		 * @pre: address_tag is populated at given index
		 * @post: address_tag is returned
		 * @param: index
		 * @return: address_tag is there, 'NULL' otherwise
		 */
		string read(int index, int cycle); 
		
		/*Gets age of last recently used address
		 * @pre: address_tag has valid entry
		 * @post: age of tag is returned
		 * @return age of last recently used address
		 */
		int lastAccessCycle(int index); 

	private: 
		string tag_array[LINE_SIZE]; 
		int* age_array[LINE_SIZE]; 
};
#endif
