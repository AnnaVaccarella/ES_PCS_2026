#pragma once
#include<vector>

template<typename T>
bool is_sorted(const std::vector<T>& vec)
{
	if (vec.size() == 0) {
		return true;
		
	}
	
	for (size_t i = 0; i<vec.size()-1; i++) {
		if (vec[i] > vec[i+1]) {
			return false;
		}
	}
	
	return true;
}

template<typename T>
void bubble_sort(std::vector<T>& vec)
{
	for(size_t i = 0; i<vec.size()-1; i++) {
		for(size_t j = vec.size()-1; j>i; j--) {
			if (vec[j] < vec[j-1]){
				T temp = vec[j];
				vec[j] = vec[j-1];
				vec[j-1] = temp;
			}
		} 
	
	}
}

template<typename T>
void insertion_sort(std::vector<T>& vec)
{
	for(size_t j = 1; j<vec.size(); j++) {
		T value = vec[j];
		int i = j-1;
		
		while(i >= 0 && vec[i] > value) {
			vec[i+1] = vec[i];
			i = i-1;
		}
		vec[i+1] = value;
	}
}
	
template<typename T>
void selection_sort(std::vector<T>& vec)
{
	for(size_t i = 0; i<vec.size()-1; i++) {
		int min_index = i;
		for(size_t j = i+1; j<vec.size(); j++) {
			if (vec[j] < vec[min_index]) {
				min_index = j;
			}
		}
		T temp = vec[i];
		vec[i] = vec[min_index];
		vec[min_index] = temp; 
	}
}