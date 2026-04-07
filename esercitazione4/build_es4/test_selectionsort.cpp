#include<iostream>
#include<vector>
#include<ctime>
#include "sort.hpp"
#include "randfiller.h"

template<typename T>
void
print_vector(const std::vector<T>& v)
{
	for (size_t i = 0; i<v.size(); i++){
		std::cout << v[i] << "\n";
	}
	std::cout << "\n";
}

int main() 
{
	std::vector<std::string> vs = {"ciao", "Torino", "Davide", "zebra", "Bergamo", "Anna", "contessa", "film", "programmazione", "calcolo", "scientifico", "Luca", "libro", "videogioco"};
	randfiller rf;
	std::srand(std::time({}));
	
	for(int i = 0; i<50; i++) {
		std::vector<int> vi;
		int dimensione = rand()%100+5;
		vi.resize(dimensione);
		
		rf.fill(vi, -100, 100);
		print_vector(vi);
		selection_sort(vi);
		print_vector(vi);
		
		if(!is_sorted(vi))
			return EXIT_FAILURE;
	}
	
	for(int i = 0; i<25; i++) {
		std::vector<float> vf;
		int dimensione2 = rand()%100+5;
		vf.resize(dimensione2);
		
		rf.fill(vf, -100.5f, 100.5f);
		print_vector(vf);
		selection_sort(vf);
		print_vector(vf);
		
		if(!is_sorted(vf))
			return EXIT_FAILURE;
	}
	
	for(int i = 0; i<25; i++) {
		std::vector<double> vd;
		int dimensione3 = rand()%100+5;
		vd.resize(dimensione3);
		
		rf.fill(vd, -112.33, 123.51);
		print_vector(vd);
		selection_sort(vd);
		print_vector(vd);
		
		if(!is_sorted(vd))
			return EXIT_FAILURE;
	}
	
	print_vector(vs);
	selection_sort(vs);
	print_vector(vs);
	
	if(!is_sorted(vs))
			return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
