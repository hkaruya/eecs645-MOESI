using namespace std; 

template<typename item>
DataCollect<item>::DataCollect(){}

template<typename item>
void DataCollect<item>::initPoint(item new_point, int init_count){
	if(isInData(new_point)) return; 

	data.push_back(data_point<item>());
	data[data.size() - 1].point = new_point; 
	data[data.size() - 1].count = init_count; 
}

template<typename item>
bool DataCollect<item>::isInData(item value) const{
	for(unsigned int i = 0; i < data.size(); i++){
		if(value == data[i].point){
			return true; 
		}
	}	
	return false; 
}

template<typename item>
bool DataCollect<item>::incrementPoint(item value){
	if(!(isInData(value))) return false; 
	
	for(unsigned int i = 0; i < data.size(); i++){
		if(value == data[i].point){
			data[i].count++; 
		}
	}
	return true; 
}

template<typename item>
bool DataCollect<item>::decrementPoint(item value){
	if(!(isInData(value))) return false; 
	
	for(unsigned int i = 0; i < data.size(); i++){
		if(value == data[i].point){
			data[i].count--; 
		}
	}
	return true; 

}

template<typename item>
void DataCollect<item>::sortData(){
	sort(data.begin(), data.end(), comparer);
}

template<typename item>
void DataCollect<item>::printData(void print(item&), bool vertical){
	for(unsigned int i = 0; i < data.size(); i++){
		print(data[i].point); 
		cout<<": "<<data[i].count<<"   ";

		if((vertical) || (i == data.size() - 1)){
			cout<<endl; 
		}
	}
}

template<typename item>
bool DataCollect<item>::comparer(data_point<item> lhs, data_point<item> rhs){
	return (lhs.point < rhs.point); 
}

template<typename item>
int DataCollect<item>::getCount(item value) const{
	if(!(isInData(value))) return -1; 

	for(unsigned int i = 0; i < data.size(); i++){
		if(value == data[i].point){
			return data[i].count;
		}
	}
	return -1; 
}

template<typename item>
int DataCollect<item>::returnSum(item value, int added_value){
	if(!(isInData(value))) return -1; 

	return (getCount(value) + added_value);
}
