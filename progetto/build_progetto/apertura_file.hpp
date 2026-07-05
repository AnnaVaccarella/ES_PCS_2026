#pragma once 
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map> 
#include "grafi.hpp"
#include <set>

struct ComponenteCircuito {   
    std::string componente;  // R1, V1, R2,...
    char tipo;   // o R o V
    double valore; // il valore di R o V
    int nodo1; 
    int nodo2;
};

struct ModelloCircuito {
    std::vector<ComponenteCircuito> elementi;
    undirected_graph grafo;
};

//Gestione degli errori
bool gestione_errori(const std::string& componente, double valore, int nodo1, int nodo2) {

    //verifica del formato della netlist 

    if (componente.size() < 2) {
        std::cerr << "Formato del componente " << componente << " non valido" << "\n";
        return false;
    }
    if (componente[0] != 'R' && componente[0] != 'V') {
        std::cerr << "Il componente " << componente << " non è valido" << "\n";
        return false;
    }
    for (size_t i = 1; i < componente.size(); i++) {
        if (!std::isdigit(componente[i])) {
            std::cerr << "Il componente " << componente << " è scritto in un formato non valido" << "\n";
            return false;
        }
    }
    if (componente[0] == 'R' && valore <= 0.0) {
        std::cerr << "Il valore negativo non è valido per la resistenza " << componente << "\n";
        return false;
    }
    if (nodo1 == nodo2) {
        std::cerr << "Il componente " << componente << " collega due nodi uguali" << "\n";
        return false;
    }
    return true;

}

//apertura file
bool apertura_file(const std::string& nome_file, ModelloCircuito& circuito) {
    std::ifstream ifs(nome_file);
    if (!ifs.is_open()) {
        std::cerr << "Non è possibile aprire il file " << nome_file << "\n";
        return false;
    }

    //ordine delle componenti
    std::string componente;
    double valore;
    int nodo1, nodo2;

    while (ifs >> componente >> valore >> nodo1 >> nodo2) { //controllo l'ordine
        if (!gestione_errori(componente, valore, nodo1, nodo2)) { // se trovo un errore non continuo a leggere il file
            return false;
        }
        ComponenteCircuito c{componente, componente[0], valore, nodo1, nodo2};
        circuito.elementi.push_back(c);
        circuito.grafo.add_edge(undirected_edge(nodo1, nodo2));
    }

    if (!ifs.eof()) {
        std::cerr << "Il formato nel file non è valido: il numero dei parametri non è sufficiente" << "\n";
        return false;
    }

    if (circuito.elementi.empty()) {
        std::cerr << "Non è presente nessun componente nel file" << "\n";
        return false;
    }

    //Controllo per almeno un resistore e almeno un generatore 
    std::vector<ComponenteCircuito> resistori, generatori;
    for (const auto& elem : circuito.elementi) {
        if (elem.tipo == 'R') {
            resistori.push_back(elem);
        }
        else {
            generatori.push_back(elem);
        }
    }
    if (resistori.empty()) {
        std::cerr << "Nessun resistore presente nel circuito" << "\n";
        return false;
    }
    if (generatori.empty()) {
        std::cerr << "Nessun generatore presente nel circuito" << "\n";
        return false;
    }

    //Non devono essere presenti collegamenti in parallelo
    std::map<undirected_edge, std::string> archi_usati; //crea una mappa vuota che associa ogni arco al nome del componente che lo occupa
    for (const auto& elem : circuito.elementi) {
        undirected_edge e(elem.nodo1, elem.nodo2);
        if (archi_usati.contains(e)) {
            std::cerr << "Il collegamento in parallelo non è ammesso tra " << archi_usati[e] << " e " << elem.componente << "\n";
            return false;
        }
        archi_usati[e] = elem.componente;
    }    

    return true;
}

//grafo connesso
bool grafo_connesso(const undirected_graph& G) {
    std::set<int>nodi = G.all_nodes();

    if (nodi.empty()) {
        return false;
    }

    std::set<int> visitati;
    std::vector<int> pila;
    int partenza = *nodi.begin();
    pila.push_back(partenza);
    visitati.insert(partenza);

    while (!pila.empty()) {
        int u = pila.back();
        pila.pop_back();

        for (int vicino : G.neighbours(u)) {
            if (!visitati.count(vicino)) {
                visitati.insert(vicino);
                pila.push_back(vicino);
            }
        }
    }
    if (visitati.size() != nodi.size()) {
        std::cerr << "Il grafo non è connesso" << "\n";
        return false;
    }
    return true;

}