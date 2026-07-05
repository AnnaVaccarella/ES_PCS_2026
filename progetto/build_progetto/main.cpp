#include <iostream>
#include <string>
#include <vector>
#include "grafi.hpp"
#include "contenitori.hpp"
#include "algoritmi.hpp"
#include "apertura_file.hpp"
#include "cicli.hpp"
#include "risolvi_sistema.hpp"

int main(int argc, const char* argv[]) {
    if (argc < 3) {
        std::cerr <<"Numero di parametri non sufficienti" << "\n";
        return EXIT_FAILURE;
    }
    std::string metodo = argv[2];
    if (metodo != "dfs" && metodo != "depina") {
        std::cerr << "Metodo non riconosciuto" << "\n";
        return EXIT_FAILURE;
    }
    
    ModelloCircuito circuito;
    //esce dal programma se apertura_file ha un errore
    if (!apertura_file((argv[1]),circuito)) {
        return EXIT_FAILURE;
    }
    
    //calcolo dei cicli fondamentali
    std::vector<std::vector<int>> cicli;
    if (metodo == "depina") {
        cicli = trova_cicli_minimi(circuito.grafo);
    }
    else {
        cicli = cicli_dfs(circuito.grafo);
    }

    if (cicli.empty()) {
        return EXIT_FAILURE;
    }

    Risultati res = risolvi_circuito(circuito, cicli);
    if (res.tensioni.size() == 0) {
        return EXIT_FAILURE;
    }

    //output
    auto misura = res.nomi.size();
    for (size_t i = 0; i < misura; i++) {
        std::cout << res.nomi[i]
                  << ": V = " << res.tensioni(i)
                  << " volts, I = " << res.correnti(i) << " amps.\n";
    }

    return EXIT_SUCCESS;
}