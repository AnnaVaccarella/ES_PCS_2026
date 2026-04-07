#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include "sort.hpp"
#include "randfiller.h"
#include "timecounter.h"

int main()
{
	randfiller rf;
	timecounter tc;
	
	std::ofstream ofs("tempi_ordinamento.csv");
	if(!ofs.is_open()){
		std::cerr << "Errore nell'apertura del file" << std::endl;
		return EXIT_FAILURE;
	}
	
	ofs << "Dimensione,BubbleSort,InsertionSort,SelectionSort,StdSort\n";
	
	for(int dim = 4; dim <= 8192; dim *= 2) {
		std::vector<int> v_base(dim);
		rf.fill(v_base,-10000,10000);
		
		std::vector<int> v_bubble = v_base;
        std::vector<int> v_insertion = v_base;
        std::vector<int> v_selection = v_base;
        std::vector<int> v_std = v_base;
		
		tc.tic();
		bubble_sort(v_bubble);
		double t_bubble = tc.toc();
		
		tc.tic();
		insertion_sort(v_insertion);
		double t_insertion = tc.toc();
		
		tc.tic();
        selection_sort(v_selection);
        double t_selection = tc.toc();
		
		tc.tic();
        std::sort(v_std.begin(), v_std.end());
        double t_std = tc.toc();
		
		ofs << dim << "," 
                << t_bubble << "," 
                << t_insertion << "," 
                << t_selection << "," 
                << t_std << "\n";
                
        std::cout << "Dimensione " << dim << " completata.\n";
	}
	
	ofs.close();
	std::cout << "File 'tempi_ordinamento.csv' generato con successo\n";
	return 0;
}