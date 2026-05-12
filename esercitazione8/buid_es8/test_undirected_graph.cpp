#include <iostream>
#include <cassert>
#include <vector>
#include "undirected_graph.hpp"

int main() {
    std::cout << "Avvio test grafo" << std::endl;
    undirected_graph<int> g;

    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(3, 1);
    
    
    assert(g.all_nodes().size() == 3); 
    
	//è stato utilizzato Gemini per la correzione dell'implementazione dei casi limite
    assert(g.neighbours(2).size() == 2);
    assert(g.neighbours(999).empty()); 
    std::cout << "Test neighbours e casi limite: Passato" << std::endl;

    undirected_edge<int> arco(1, 2);
    int idx = g.edge_number(arco);
    auto recuperato = g.edge_at(idx);
    assert(recuperato.has_value() && *recuperato == arco);
    std::cout << "Test indicizzazione: Passato" << std::endl;

    
    undirected_graph<int> g_sub;
    g_sub.add_edge(1, 2);
    undirected_graph<int> res = g - g_sub;
    assert(res.all_edges().size() == 2);
    std::cout << "Test differenza: Passato" << std::endl;

    std::cout << "Tutti i test del grafo passati!" << std::endl;
    return 0;
}