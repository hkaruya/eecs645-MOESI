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
		//Initializes DataCollect data structure
		//Utilizes data_point structure where an item is paired with a count
		DataCollect(); 

		//Initilizes new point with given count, pair
		//@param: new_point
		//@param: init_count, starting count for object
		void initPoint(item new_point, int init_count); 

		//Used to check if value is and element in data set
		//@param: value, key to search for
		//@return: true if item is in dataset, false otherwise
		bool isInData(item value) const; 

		//Increments value count of given value
		//@param: value
		//@return: true once incremented, false if value is not part of dataset
		bool incrementPoint(item value); 

		//Decrements value count of given value
		//@param: value
		//@return: true once item is decremented, false if value is not part of dataset
		bool decrementPoint(item value); 

		//Sorts the data with in dataset
		void sortData(); 

		//Prints data within dataset(value: count)
		//@param: print(item&) function used to print item
		//@param: vertical, indicates how to print data
		void printData(void print(item&), bool vertical); 

		//Returns count of value
		//@param: item
		int getCount(item value) const; 
		
		//Returns the count of value summed with added value
		//@param: value
		//@param: added_value
		int returnSum(item value, int added_value);
	private:
		//Helper function used in sort function
		static bool comparer(data_point<item> lhs, data_point<item> rhs);

		vector<data_point<item>> data; 
};
#include "data-collect.hpp"
#endif
