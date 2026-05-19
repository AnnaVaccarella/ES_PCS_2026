#pragma once

#include<iostream>
#include<queue>
#include<limits>
#include<vector>
#include<set>
#include<map>
#include "undirected_graph.hpp"


template<typename T, typename Contenitore>
undirected_graph<T> graph_visit(const undirected_graph<T>& grafo, const T& nodo_partenza, Contenitore da_visitare) {
	undirected_graph<T> albero;
	std::set<T> visitati;
	std::map<T,T> padre;
	
	da_visitare.put(nodo_partenza);
	
	while(!da_visitare.empty()) {
		T corrente = da_visitare.get();
		
		if(visitati.find(corrente) == visitati.end()) {
			visitati.insert(corrente);
			std::cout<< corrente << " ";
			
			if(corrente != nodo_partenza) {
				albero.add_edge(padre[corrente], corrente);
			}
			
			for(const T& vicino : grafo.neighbours(corrente)) {
				if(visitati.find(vicino) == visitati.end()) {
					da_visitare.put(vicino);
					
					if(padre.find(vicino)  == padre.end()){
						padre[vicino] = corrente;
					}
				}
			}
		}
	}
	
	std::cout << std::endl;
	return albero;
}

template<typename T>
void dfs_helper(const undirected_graph<T>& grafo, const T& nodo_sorgente, std::set<T>& visitati, undirected_graph<T>& albero) {
	visitati.insert(nodo_sorgente);
	
	for(const T& vicino: grafo.neighbours(nodo_sorgente)) {
		if(visitati.find(vicino) == visitati.end()) {
			albero.add_edge(nodo_sorgente, vicino);
			dfs_helper(grafo,vicino,visitati,albero);
		}
	}
}

template<typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& grafo, const T& nodo_sorgente) {
	undirected_graph<T> albero_risultante;
	std::set<T> visitati;
	
	dfs_helper(grafo, nodo_sorgente, visitati, albero_risultante);
	
	return albero_risultante;
}


template<typename T>
std::map<T, int> dijkstra(const undirected_graph<T>& grafo, const T& nodo_sorgente) {
    std::map<T, int> distanze;
  
    for (const T& nodo : grafo.all_nodes()) {
        distanze[nodo] = std::numeric_limits<int>::max();
    }
    
    distanze[nodo_sorgente] = 0;
    
    std::priority_queue<
        std::pair<int, T>, 
        std::vector<std::pair<int, T>>, 
        std::greater<std::pair<int, T>>
    > coda_priorita;
    
    coda_priorita.push({0, nodo_sorgente});

    while (!coda_priorita.empty()) {
        int dist_corrente = coda_priorita.top().first;
        T corrente = coda_priorita.top().second;
        coda_priorita.pop();

        
        if (dist_corrente > distanze[corrente]) continue;

        
        for (const T& vicino : grafo.neighbours(corrente)) {
            int peso_arco = 1; 
            int nuova_distanza = dist_corrente + peso_arco;

            
            if (nuova_distanza < distanze[vicino]) {
                distanze[vicino] = nuova_distanza;
                coda_priorita.push({nuova_distanza, vicino});
            }
        }
    }

    return distanze;
}