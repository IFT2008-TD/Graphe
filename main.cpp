#include <iostream>
#include <string>
#include "Graphe.h"
#include "graphes_algorithmes.h"

int main() {
    Graphe<std::string, int> graphe({"A", "B", "C", "D", "E"}) ;

    graphe.ajouterUneArete("A", "B", 0) ;
    graphe.ajouterUneArete("A", "C", 0) ;
    graphe.ajouterUneArete("C", "D", 0) ;
    graphe.ajouterUneArete("D", "E", 0) ;
    graphe.ajouterUneArete("C", "E", 0) ;

    auto resultat = explorer_DFS(graphe) ;
    std::cout << "Résultat de la visite en profondeur\n" ;
    while (!resultat.empty()) {
        std::cout << "Sommet: " << resultat.top() << std::endl ;
        resultat.pop() ;
    }

    auto ginv = construireInverse(graphe) ;

    return 0;
}
