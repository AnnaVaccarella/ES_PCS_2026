#pragma once
#include "grafi.hpp"
#include <set>
#include <map>
#include <queue>
#include <limits>
#include <functional>

//dfs ricorsiva
undirected_graph recursive_dfs(const undirected_graph& G, int nodo_sorgente) {
	undirected_graph grafo;
	std::set<int> visitato;
	std::function<void(int)> dfs = [&G, &visitato, &grafo, &dfs] (int u) {
		visitato.insert(u);
		for (int vicino : G.neighbours(u)) {
			if (!visitato.count(vicino)) {
				grafo.add_edge(undirected_edge(u, vicino));
				dfs(vicino); //chiamata ricorsiva
			}
		}
	};
	dfs(nodo_sorgente);
	return grafo;
}

//Dijkstra
struct DistanzaNodo {
	int distanza;
	int posizione_nodo;
	bool operator<(const DistanzaNodo& altro) const {
		return distanza > altro.distanza;
	}
};
	

undirected_graph dijkstra(const undirected_graph& G, int nodo_sorgente) {
	std::map<int, int> dist; //array delle distanze
	std::map<int, int> pred; //array dei predecessori
	std::set<int> nodi = G.all_nodes();
	
	//costante per l'infinito sicuro
	const int INF = std::numeric_limits<int>::max();

	for (int i : nodi) {
		pred[i] = -1;   //inizializza a -1
		dist[i] = INF; //inizializza a +infinito 
	}
	pred[nodo_sorgente] = 0;
	dist[nodo_sorgente] = 0;
	
	//coda con priorità usando DistanzaNodo
	std::priority_queue<DistanzaNodo> PQ;
	//enqueue iniziale di tutti i nodi
	for (int i : nodi) {
		PQ.push({dist[i], i});
	}
	
	while (!PQ.empty()) {
		//dequeue : estraggo il nodo con la distanza minore
		int d = PQ.top().distanza;
		int n = PQ.top().posizione_nodo;
		PQ.pop();
		
		//se la distanza è stata già vista o è maggiore di quella salvata, ignoro
		if (d > dist[n]) continue;
		
		for (int w : G.neighbours(n)) {
			int peso = 1; // il grafo non è pesato, assumo che peso = 1
			
			//usiamo dist[n]+peso solo se dist[n] non è infiinito, ma dato che estraiamo solo nodi raggiunti, dist[n] è sempre un numero valido
			if (dist[w] > dist[n] + peso) {
				dist[w] = dist[n] + peso;
				pred[w] = n;
				
				PQ.push({dist[w], w});
			}
		}
	}
	
	//costruzione del grafo
	undirected_graph grafo;
	for (int i : nodi) {
		//se il nodo ha un nodo precedente valido e non è la sorgente
		if (pred[i] != -1 && pred[i] != i) {
			grafo.add_edge(undirected_edge(pred[i], i));
		}
	}
	return grafo;
}