#include <iostream>
#include <cassert>
#include "undirected_edge.hpp"

int main() {
	std::cout << "Inizio test" << std:: endl;
	
	undirected_edge<int> e1(28,14);
	
	assert(e1.from() == 14);
	assert(e1.to() == 28);
	
    std::cout << " Normalizzazione (from < to): passata" << std::endl;

    
    undirected_edge<int> e2(14, 28);
    assert(e1 == e2); 
    std::cout <<"Operatore == : passato" << std::endl;

    
    undirected_edge<int> e3(12, 100);
    assert(e3 < e1);
    std::cout << "Operatore < : passato" << std::endl;


    std::cout << "Visualizzazione arco: " << e1 << std::endl;

    std::cout << "Tutti i test sono stati superati" << std::endl;

    return 0;
}
	
