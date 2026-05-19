#include <iostream>
#include <fstream>
#include <string>
#include "undirected_graph.hpp"
#include "classi.hpp"
#include "graph_algoritmi.hpp"

//per salva_grafo_dot il codice è stato corretto da Gemini
template<typename T>
void salva_grafo_dot(const undirected_graph<T>& grafo, const std::string& nome_file) {
    std::ofstream out(nome_file);
    if(!out) {
        std::cerr << "Errore: impossibile creare il file " << nome_file << std::endl;
        return;
    }
    
    out << "graph G {\n";
    out << " node [shape=circle]; \n";
    
    for(const T& nodo: grafo.all_nodes()) {
        out << " \"" << nodo << "\"; \n";
    }
    
    for(const auto& arco: grafo.all_edges()) {
        out << " \"" << arco.from() << "\" -- \"" << arco.to() << "\";\n";
    }
    
    out << "}\n";
    out.close();
    std::cout << "File " << nome_file << " generato con successo." << std::endl;
}

int main() {
    undirected_graph<int> grafo;
    grafo.add_edge(3, 5);
    grafo.add_edge(5, 2);
	grafo.add_edge(2, 7);
    grafo.add_edge(7, 3);
    grafo.add_edge(7, 4);
	grafo.add_edge(3, 4);
    int nodo_partenza = 3;

    std::cout << "Visita in profondita' (DFS): ";
    pila<int> s;
    auto dfsG = graph_visit(grafo, nodo_partenza, s);
    salva_grafo_dot(dfsG, "dfs.dot");
    
    std::cout << "Visita in ampiezza (BFS): ";
    coda<int> q;
    auto bfsG = graph_visit(grafo, nodo_partenza, q);
    salva_grafo_dot(bfsG, "bfs.dot");
    
    
    salva_grafo_dot(grafo, "originale.dot");

    
    std::cout << "\nTest Dijkstra dal nodo " << nodo_partenza << ":" << std::endl;
    auto distanze = dijkstra(grafo, nodo_partenza);
    for(const auto& [nodo, dist] : distanze) {
        if(dist == std::numeric_limits<int>::max()) {
            std::cout << "Nodo " << nodo << " irraggiungibile." << std::endl;
        } else {
            std::cout << "Distanza fino al nodo " << nodo << " : " << dist << std::endl;
        }
    }

    return 0;
}