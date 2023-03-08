//
// Created by Pascal Charpentier on 2023-03-07.
//

#ifndef GRAPHE_BASE_RESOLVEURDIJKSTRA_H
#define GRAPHE_BASE_RESOLVEURDIJKSTRA_H

#include "Graphe.h"
#include <map>
#include <unordered_map>
#include <limits>

template <typename T>
class ResolveurDijkstra {

public:
    struct ResultatsDijkstra {
        std::unordered_map<T, double> distances;
        std::unordered_map<T, T> predecesseurs;
    };

public:
    explicit ResolveurDijkstra(const Graphe<T, double>& graphe) ;

    void resoudre (const T& depart) ;

    void initResolveur (const T& depart) ;

    struct ResultatsDijkstra resultats () const ;

private:
    Graphe<T, double> graphe;

    std::unordered_map<T, double> nonResolus;

    bool estResolu;

    std::unordered_map<T, double> distances;
    std::unordered_map<T, T> predecesseurs;

private:
    T    trouverProchainNonResolu () const ;
    void relaxer(const T& depart, const T& arrivee) ;

} ;



#include "ResolveurDijkstra_implantation.h"








#endif //GRAPHE_BASE_RESOLVEURDIJKSTRA_H
