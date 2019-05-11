#ifndef DATA_COLLECT_H
#define DATA_COLLECT_H
#include <vector>
#include <bits/stdc++.h>
#include <iostream>

using namespace std; 

template<typename struct_item>
struct data_point{
	struct_item point; 
	int count; 
}; 

template<typename item>
class DataCollect{
	public:
		DataCollect(); 
		void initPoint(item new_point, int init_count); 
		bool isInData(item value); 
		bool incrementPoint(item value); 
		bool decrementPoint(item value); 

		void sortData(); 
		void printData(void print(item&), bool vertical); 
	private:
		static bool comparer(data_point<item> lhs, data_point<item> rhs);

		vector<data_point<item>> data; 
};
#include "data-collect.hpp"
#endif
