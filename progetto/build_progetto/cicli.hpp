#pragma once 
#include <vector>
#include <iostream>
#include <limits>
#include <set> 
#include <map> 
#include "grafi.hpp"
#include "algoritmi.hpp"

//trova il percorso tra u e v
bool findpath(const undirected_graph& T, int u, int v, std::set<int>& nodi_visitati, std::vector<int>& percorso) {
    nodi_visitati.insert(u); //aggiungo u (nodo corrente) ai nodi visitati
    percorso.push_back(u);
    if (u == v) { // se il nodo corrente è la destinazione, il percorso è completo
        return true;
    }
    for (int n : T.neighbours(u)) {
        if (!nodi_visitati.count(n) && findpath(T, n, v, nodi_visitati, percorso)) {  
            return true;
        }
    }  
    percorso.pop_back(); //se il percorso è sbagliato, togli l'ultimo nodo visitato
    return false;
}

//calcolo i cicli fondamentali con DFS
std::vector<std::vector<int>> cicli_dfs(const undirected_graph& G) {
    auto nodi = G.all_nodes(); //salvo tutti i nodi
    if (nodi.empty()) {
        return{};
    }

    undirected_graph T = recursive_dfs(G, *nodi.begin());
    undirected_graph C = G - T;

    std::vector <std::vector<int>> cicli;
    for (const auto& arco : C.all_edges()) {
        std::set<int> nodi_visitati;
        std::vector<int> percorso;
        if (findpath(T, arco.from(), arco.to(), nodi_visitati, percorso)) {
            cicli.push_back(percorso);
        }
    }
    return cicli;
}

//calcolo i cicli minimi con De Pina

//calcolo il prodotto scalare
int prodotto_scalare(const std::vector<bool>& S, const std::vector<bool>& P) {
    int prodotto = 0;
    for (size_t i = 0; i < S.size(); i++) {
        prodotto ^= (int)(S[i] && P[i]); //S[i] && P[i] = 1 se e solo se entrambi 1; tutto il risultato vale 1 solo se prodotto di S[i] && P[i] hanno valori diversi
    }
    return prodotto;
}

//calcolo la differenza simmetrica
std::vector<bool> differenza_simmetrica(const std::vector<bool>& S, const std::vector<bool>& P) {
    std::vector<bool> differenza(S.size()); //essendo bool, la differenza è un vettore con tutti 0
    for (size_t i = 0; i < S.size(); i++) {
        differenza[i] = S[i] ^ P[i];
    }
    return differenza;
}

//Creo un grafo ausiliario per trovare il ciclo minimo

//duplico i vertici del grafo: costruisco v+ e v- in modo da non sovrapporre nodi originali e copie
 int v_piu(int v) {
    return v;
}
int v_meno(int v, int N) {
    return v + N;
}


//trovo cicli minimi
std::vector<std::vector<int>> trova_cicli_minimi(const undirected_graph& G) {
    auto nodi = G.all_nodes();
    undirected_graph T = recursive_dfs(G, *nodi.begin());
    undirected_graph C =  G - T;
    auto archi = G.all_edges();
    auto numero_archi = G.all_edges().size();

    //mappa per i vettori di incidenza
    std::map<undirected_edge, int> archi_incidenza;
    int indice = 0;
    for (const auto& e : archi) {
        archi_incidenza[e] = indice++;
    }

    auto archi_C = C.all_edges();
    
    int numero_cicli_fond = (int)archi_C.size(); //il numero di cicli fondamentali è il numero degli archi di C
    
    std::vector<std::vector<bool>> S(numero_cicli_fond, std::vector<bool>(numero_archi));
    for (int i = 0; i < numero_cicli_fond; i++) {
        if (archi_incidenza.count(archi_C[i])) {
            S[i][archi_incidenza[archi_C[i]]] = true;
        }
    }
    int N = *nodi.rbegin() + 1; //rbegin punta dalla fine verso l'inizio

    std::vector<std::vector<int>> cicli;
    for (int i = 0; i < numero_cicli_fond; i++) {
        undirected_graph G_primo;
        auto it_archi = archi.begin();
        //aggiungo archi
        for (size_t k = 0; k < numero_archi; k++, ++it_archi) { // k è l'indice per numerare gli archi
            int u = (*it_archi).from(); 
            int v = (*it_archi).to();
            if (S[i][k]) {
                G_primo.add_edge(undirected_edge(v_piu(u), v_meno(v,N)));
                G_primo.add_edge(undirected_edge(v_piu(v), v_meno(u,N)));
            }
            else {
                G_primo.add_edge(undirected_edge(v_piu(u), v_piu(v)));   
                G_primo.add_edge(undirected_edge(v_meno(u,N), v_meno(v,N)));
            }

        }
        //calcolo cammino minimo
        std::vector<bool> miglior_ciclo;
        int lunghezza_ciclo_migliore = std::numeric_limits<int>::max(); //prendo un numero molto grande
        for (int v : nodi) {
            undirected_graph T_primo = dijkstra(G_primo, v_meno(v,N)); //albero dei cammini minimi partendo da v_meno
            std::set<int> visitati;
            std::vector<int> percorso;
            if (!findpath(T_primo, v_meno(v,N), v_piu(v), visitati, percorso)) { //se non esiste il cammino da v_meno a v_piu dentro l'albero dei cammini minimi T_primo
                continue;
            }
            //trasformo il cammino trovato nel grafo G_primo in un ciclo del grafo G
            std::vector<bool> candidato(numero_archi); //vettore di incidenza del ciclo
            for (int p = 0; p + 1 < (int)percorso.size(); p++) { // p indica l'inizio del percorso
                int p1 = percorso[p]; 
                int p2 = percorso[p+1]; //  p1 e p2 sono due nodi consecutivi del percorso
                if (p1 >= N) { // se p1 è una copia negativa, allora lo riporto al nodo originale
                    p1 = p1 - N;
                }
                if (p2 >= N) {
                    p2 = p2 - N; 
                } // ora p1 e p2 sono nodi del grafo originale G
                undirected_edge arco(p1, p2); //crea un arco da p1 a p2 di G
                if (archi_incidenza.count(arco)) { // se l'arco esiste nella mappa
                    int ind = archi_incidenza[arco]; //recupero la posizione dell'arco dal vettore incidenza
                    candidato[ind] = !candidato[ind]; //aggiorno il vettore d'incidenza
                }  
            }
            int lunghezza_ciclo = 0;
            for (bool presente : candidato) { // fino a che candidato è nel ciclo
                if (presente) { // se è presente aggiorna la lunghezza del ciclo
                    lunghezza_ciclo++;
                }
            }
            if (prodotto_scalare(candidato, S[i]) == 1 && lunghezza_ciclo < lunghezza_ciclo_migliore) {
                lunghezza_ciclo_migliore = lunghezza_ciclo;
                miglior_ciclo = candidato;
            }
        }
        //conservo il ciclo con il più piccolo numero di elementi 1

        //converto un vettore di incidenza nella sequenza di nodi che percorre il ciclo
        std::map<int, std::vector<int>> adiacenza;
        auto iteratore = archi.begin();
        for (size_t e = 0; e < miglior_ciclo.size(); e++, ++iteratore) {
            if (miglior_ciclo[e]) {
                int u = iteratore->from();
                int v = iteratore->to();
                adiacenza[u].push_back(v);
                adiacenza[v].push_back(u);
            }
        }
        if (adiacenza.empty()) {
            return {};
        }

        int partenza = adiacenza.begin()->first; 
        std::vector<int> ciclo;
        int corrente = partenza;
        int precedente = -1;

        ciclo.push_back(partenza);
        while (true) {
            int prossimo = -1;
            for (int vicino : adiacenza[corrente]) {
                if (vicino != precedente) {
                    prossimo = vicino;
                    break;
                }
            }
            if (prossimo == -1) {
                return {};
            }
            precedente = corrente;
            corrente = prossimo;

            if (corrente == partenza) {
                break;
            }
            ciclo.push_back(corrente);
        }

        cicli.push_back(ciclo);

        // S[j] = S[j] XOR miglior ciclo per tutti j > i con prodotto scalare = 1
        for (int j = i + 1; j < numero_cicli_fond; j++) {
            if (prodotto_scalare(miglior_ciclo, S[j]) == 1) {
                S[j] = differenza_simmetrica(S[j], miglior_ciclo);
            }
        }
    }
    return cicli;
}
