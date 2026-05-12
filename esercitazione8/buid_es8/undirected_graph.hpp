#pragma once

 
#include <vector>
#include <set>
#include <optional>
#include <algorithm>
#include <iterator>
#include "undirected_edge.hpp"

template<typename T>
class undirected_graph {
private:
    std::set<T> nodi;
    std::set<undirected_edge<T>> archi;

public:
    undirected_graph() = default;
    undirected_graph(const undirected_graph& other) : nodi(other.nodi), archi(other.archi) {}
    
    std::vector<T> neighbours(const T& nodo_cercato) const {
        std::vector<T> vicini;
        if (nodi.find(nodo_cercato) == nodi.end()) return vicini;
        for (const auto& arco : archi) {
            if (arco.from() == nodo_cercato) vicini.push_back(arco.to());
            else if (arco.to() == nodo_cercato) vicini.push_back(arco.from());
        }
        return vicini;
    }
    
    bool add_edge(const T& nodo_a, const T& nodo_b) {
        nodi.insert(nodo_a);
        nodi.insert(nodo_b);
        auto result = archi.insert(undirected_edge<T>(nodo_a, nodo_b));
        return result.second;
    }
        
    std::vector<undirected_edge<T>> all_edges() const {
        return std::vector<undirected_edge<T>>(archi.begin(), archi.end());
    }
    
    std::vector<T> all_nodes() const {
        return std::vector<T>(nodi.begin(), nodi.end());
    }
    
    int edge_number(const undirected_edge<T>& arco_cercato) const {
        auto it = archi.find(arco_cercato);
        if (it == archi.end()) return -1;
        return static_cast<int>(std::distance(archi.begin(), it));
    }

    std::optional<undirected_edge<T>> edge_at(size_t index) const {
        if (index >= archi.size()) return std::nullopt;
        return *std::next(archi.begin(), index);
    }
    
	//è stato utilizzato l'assistente Gemini per correggere l'implementazione dell'operatore differenza tra grafi, utilizzando std::set_difference combinato con std::inserter
    undirected_graph<T> operator-(const undirected_graph<T>& other) const {
        undirected_graph<T> risultato;
        std::set_difference(
            this->archi.begin(), this->archi.end(),
            other.archi.begin(), other.archi.end(),
            std::inserter(risultato.archi, risultato.archi.begin())
        );
        for (const auto& arco : risultato.archi) {
            risultato.nodi.insert(arco.from());
            risultato.nodi.insert(arco.to());
        }
        return risultato;
    }
};