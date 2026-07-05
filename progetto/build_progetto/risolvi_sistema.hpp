#pragma once
#include <vector>
#include <Eigen/Dense>
#include "grafi.hpp"
#include "apertura_file.hpp"

using Matrice = Eigen::MatrixXd;
using Vettore = Eigen::VectorXd;

//memorizza tensioni e correnti nei resistori
struct Risultati {
    std::vector<std::string> nomi;
    Vettore tensioni;
    Vettore correnti;
};

Risultati risolvi_circuito(const ModelloCircuito& circuito, const std::vector<std::vector<int>>& cicli) {
    //separo resistori e generatori
    std::vector<ComponenteCircuito> resistori, generatori;
    for (const auto& elem : circuito.elementi) {
        if (elem.tipo == 'R') {
            resistori.push_back(elem);
        }
        else {
            generatori.push_back(elem);
        }
    }
    //memorizzo il numero di resistori e di maglie per avere la dimensione della matrice di incidenza
    auto num_r = resistori.size();
    auto num_maglie = cicli.size();

    //assemblaggio di B e v
    Matrice B = Matrice::Zero(num_r,num_maglie);
    Vettore v = Vettore::Zero(num_maglie);

    for (size_t j = 0; j < num_maglie; j++) {
        const auto& ciclo = cicli[j];
        auto lungh_ciclo = ciclo.size(); //memorizzo la lunghezza del ciclo j-esimo

        for (size_t passo = 0; passo < lungh_ciclo; passo++) {
            int u1 = ciclo[passo];
            int v1 = ciclo[(passo + 1) % lungh_ciclo]; // % lungh_ciclo serve per tornare dall'ultimo nodo al primo
            undirected_edge e(u1,v1);

            //riempimento B
            for (size_t i = 0; i < num_r; i++) {
                undirected_edge r(resistori[i].nodo1, resistori[i].nodo2);
                if (r == e) {
                    if (u1 < v1) {
                        B(i,j) = +1;
                    } 
                    else {
                        B(i,j) = -1;
                    }
                }
            }
            //riempimento v
            for (const auto& gen : generatori) {
                undirected_edge g(gen.nodo1, gen.nodo2);
                if (g == e) {
                    if (u1 == gen.nodo1) {
                        v(j) -= gen.valore; // se il ciclo entra nel generatore da (+) a (-), il contributo è negativo
                    }
                    else {
                        v(j) += gen.valore;
                    }
                }
            }
        }
    }
    //assemblaggio R
    Matrice R = Matrice::Zero(num_r,num_r);
    for (size_t i = 0; i < num_r; i++) {
        R(i,i) = resistori[i].valore;
    }

    //risoluzione del sistema B^T * R * B * i = v
    Eigen::PartialPivLU<Matrice> lu(B.transpose() * R * B);
    Vettore corrente_maglia = lu.solve(v);

    //calcolo delle tensioni e delle correnti sui resistori
    Vettore v_r = R * B * corrente_maglia;
    Vettore i_r = B * corrente_maglia;

    Risultati res; //inizializza
    res.tensioni = v_r;
    res.correnti = i_r;
    for (size_t k = 0; k < num_r; k++) {
        res.nomi.push_back(resistori[k].componente);
    }
    return res;
}