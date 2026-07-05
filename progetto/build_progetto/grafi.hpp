#pragma once
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>

//implemento la classe arco in un grafo non orientato
class undirected_edge {
private:
	int n_from;
	int n_to;
	
public:
	//è sempre garantito che from è minore di to
	undirected_edge(int n1, int n2) {
		n_from = std::min(n1, n2);
		n_to = std::max(n1, n2);
	}
	
	//per restituire i due nodi dell'arco
	int from() const {
		return n_from;
	}
	
	int to() const {
		return n_to;
	}
	
	//operatore < in modo da rendere ordinabili gli archi
	bool operator<(const undirected_edge& other) const {
		if (n_from != other.n_from) {
			return n_from < other.n_from;
		}
		return n_to < other.n_to;
	}
	
	//operatore == in per avere l'uguaglianza
	bool operator==(const undirected_edge& other) const {
		return n_from == other.n_from && n_to == other.n_to;
	}
};

//operatore << 
std::ostream& operator<<(std::ostream& os, const undirected_edge& edge) {
	os<<"(" <<edge.from() <<", " << edge.to() << ")";
	return os;
}

//implemento un grafo non orientato
class undirected_graph{
	private:
	//lista di adiacenza, permette di capire quali nodi sono collegati ad un certo nodo X
	std::unordered_map<int, std::set<int>> adiacenza;
	//mantiene l'ordine lessicografico di inserimento
	std::vector<undirected_edge> edges_per_indice;
	//permette di trovare l'indice di un arco in modo rapido
	std::map<undirected_edge, int> edge_indice;
	
	
	public:
	//costruttore di default
	undirected_graph() = default;
			
	//costruttore di copia
	undirected_graph(const undirected_graph&) = default;
		
		
	//metodo neighbours() che restituisce i nodi vicini di un nodo
	std::set<int> neighbours(int nodo) const {
		auto iteratore = adiacenza.find(nodo);
		if (iteratore == adiacenza.end()) {
			return {};
		}
		return (*iteratore).second;
	}
	
	//metodo add_edge() che permette di aggiungere un arco al grafo
	void add_edge(const undirected_edge& edge) {
		if (edge_indice.find(edge) != edge_indice.end()) {   // se l'arco esiste già, non lo aggiungo
			return;
		}
		//calcolo il nuovo indice per l'arco che devo inserire
		size_t indice = edges_per_indice.size();
		//aggiungo l'arco alla fine
		edges_per_indice.push_back(edge);
		edge_indice[edge] = indice;
		
		adiacenza[edge.from()].insert(edge.to());
		adiacenza[edge.to()].insert(edge.from());
	}
	
	//metodo all_edges() che restituisce tutti gli archi
	const std::vector<undirected_edge>& all_edges() const {
    return edges_per_indice;
}
	
	//metodo all_nodes() che restituisce tutti i nodi
	std::set<int> all_nodes() const {
		std::set<int> nodi;
		
		for (const auto& coppia : adiacenza){
			nodi.insert(coppia.first);
		}
		return nodi;
	}
	
	//metodo edge_number() che, dato un arco, ne restituisce la sua numerazione nel grafo
	bool edge_number(const undirected_edge& edge, int& posizione_arco) const {
		int indice = 0;
		
		for (const auto& arco : edges_per_indice) {
			if (arco == edge) {
				posizione_arco = indice;
				return true;
			}
			indice++;
		}
		return false;
	}
	
	//metodo edge_at() che, dato un numero d’arco, restituisce il corrispondente oggetto arco nel grafo
	bool edge_at(int index, undirected_edge& arco_trovato) const {
		int indice = 0;
		
		for (const auto& arco : edges_per_indice) {
			if (indice == index) {
				arco_trovato = arco;
				return true;
			}
			indice++;
		}
		return false;
	}
	
	
	//operator-() permette di calcolare la differenza tra due grafi
	undirected_graph operator-(const undirected_graph& other) const {
		undirected_graph result; //si crea un grafo vuoto dove si mette la differenza
		for (const auto& edge : edges_per_indice) {
			if (other.edge_indice.find(edge) == other.edge_indice.end()) {
				result.add_edge(edge);
			}
		}
		return result;
	}
};