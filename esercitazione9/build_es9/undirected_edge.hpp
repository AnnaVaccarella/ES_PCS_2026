#pragma once
#include <iostream>
#include <algorithm>

template<typename T>
class undirected_edge {
    T nodo_1;
    T nodo_2;
    
public:
    undirected_edge(T n_a, T n_b) {
        
        nodo_1 = std::min(n_a, n_b);
        nodo_2 = std::max(n_a, n_b);
    }
    
    T from() const { return nodo_1; }
    T to() const { return nodo_2; }
    
    bool operator<(const undirected_edge<T>& other) const {
        if (nodo_1 != other.nodo_1) {
            return nodo_1 < other.nodo_1;
        }
        return nodo_2 < other.nodo_2;
    }
    
    bool operator==(const undirected_edge<T>& other) const {
        return (nodo_1 == other.nodo_1 && nodo_2 == other.nodo_2);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& edge) {
    os << "{" << edge.from() << " - " << edge.to() << "}";
    return os;
}