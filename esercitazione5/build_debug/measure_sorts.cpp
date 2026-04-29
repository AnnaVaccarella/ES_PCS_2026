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
	
	ofs << "Dimensione,BubbleSort,InsertionSort,SelectionSort,MergeSort,QuickSort,StdSort\n";
	
	for(int dim = 2; dim <= 64; dim *= 2) {
		std::vector<std::vector<double>> v_base(150);
		
		for(int i = 0; i < 150; i++) {
			std::vector<double> v_double(dim);
			rf.fill(v_double,-10000.0,10000.0);
			v_base[i] = v_double;
		}
		
		std::vector<std::vector<double>> v_bubble = v_base;
        std::vector<std::vector<double>> v_insertion = v_base;
        std::vector<std::vector<double>> v_selection = v_base;
		std::vector<std::vector<double>> v_merge = v_base;
		std::vector<std::vector<double>> v_quick = v_base;
        std::vector<std::vector<double>> v_std = v_base;
		
		tc.tic();
		for(size_t i = 0; i < v_bubble.size(); i++) {
			bubble_sort(v_bubble[i]);
		}
		double t_bubble = tc.toc()/v_bubble.size();
		
		tc.tic();
		for(size_t i = 0; i < v_insertion.size(); i++) {
			insertion_sort(v_insertion[i]);
		}
		double t_insertion = tc.toc()/v_insertion.size();
		
		tc.tic();
        for(size_t i = 0; i < v_selection.size(); i++) {
			selection_sort(v_selection[i]);
		}
		double t_selection = tc.toc()/v_selection.size();
		
		tc.tic();
        for(size_t i = 0; i < v_merge.size(); i++) {
			merge_sort(v_merge[i], 0, v_merge[i].size()-1);
		}
		double t_merge = tc.toc()/ v_merge.size();
		
		tc.tic();
        for(size_t i = 0; i < v_quick.size(); i++) {
			quick_sort(v_quick[i], 0, v_quick[i].size()-1);
		}
		double t_quick = tc.toc()/v_quick.size();
		
		tc.tic();
        for(size_t i = 0; i < v_std.size(); i++) {
			std::sort(v_std[i].begin(), v_std[i].end());
		}
        double t_std = tc.toc()/v_std.size();
		
		ofs << dim << "," 
                << t_bubble << "," 
                << t_insertion << "," 
                << t_selection << "," 
				<< t_merge << ","
				<< t_quick << ","
                << t_std << "\n";
                
        std::cout << "Dimensione " << dim << " completata.\n";
	}
	
	ofs.close();
	std::cout << "File 'tempi_ordinamento.csv' generato con successo\n";
	return 0;
}