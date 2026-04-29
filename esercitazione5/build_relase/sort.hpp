#pragma once
#include<vector>
#include<algorithm>

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

template<typename T>
void merge(std::vector<T>& vec, int p, int q, int r)
{
	int n1 = q-p+1;
	int n2 = r-q;
	
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	
	for(int i = 0; i < n1; i++) {
		L[i] = vec[p+i];
	}
	
	for(int j = 0; j < n2; j++) {
		R[j] = vec[q+1+j];
	}
	
	int i = 0;
	int j = 0;
	int k = p;
	
	while (i<n1 && j<n2) {
		if(L[i] <= R[j]) {
			vec[k] = L[i];
			i++;
	}
		else {
			vec[k] = R[j];
			j++;
		}
		k++;
	}
	
	while (i<n1) {
		vec[k] = L[i];
		i++;
		k++;
	}
	
	while (j<n2) {
		vec[k] = R[j];
		j++;
		k++;
	}
}

template<typename T>
void merge_sort(std::vector<T>& vec, int p, int r)
{
	if(p<r) {
		int q = (p+r)/2;
		merge_sort(vec,p,q);
		merge_sort(vec,q+1,r);
		merge(vec,p,q,r);
	}
}

template<typename T>
int partition(std::vector<T>& vec, int p, int r)
{
	T x = vec[r];
	int i = p-1;
	
	for(int j=p; j<r; j++){
		if(vec[j]<=x){
			i = i+1;
			T temp = vec[i];
			vec[i] = vec[j];
			vec[j] = temp;
		}
	}
	
	T temp1 = vec[i+1];
	vec[i+1] = vec[r];
	vec[r] = temp1;
	
	return i+1;
}

template<typename T>
void quick_sort(std::vector<T>& vec, int p, int r)
{
	if(p<r){
		int q = partition(vec, p, r);
		quick_sort(vec,p,q-1);
		quick_sort(vec, q+1, r);	
	}
}

template<typename T>
void quick_sort_migliorato(std::vector<T>& vec, int p, int r) {
    if (p < r) {
        // Se la dimensione del sottovettore è minore di 16, usare std::sort per l'ordinamento dell'intervallo [p,r] dell'array
        if (r - p + 1 < 16) { 
            std::sort(vec.begin()+p, vec.begin()+r+1); 
        } else {
            int q = partition(vec, p, r);
            quick_sort_migliorato(vec, p, q - 1);
            quick_sort_migliorato(vec, q + 1, r);
        }
    }
}