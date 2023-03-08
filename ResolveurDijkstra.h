//
// Created by Pascal Charpentier on 2023-03-07.
//

#ifndef GRAPHE_BASE_RESOLVEURDIJKSTRA_H
#define GRAPHE_BASE_RESOLVEURDIJKSTRA_H

#include "Graphe.h"
#include <map>
#include <unordered_map>
#include <limits>

/**
 * Voici une classe permettant d'appliquer l'algorithme de Dijkstra à un objet Graphe.  L'utilisation d'une classe
 * comporte des avantages: les algorithmes proposés classiquement dans les livres utilisent souvent des structures
 * de données ayant une portée globale.  Nous pouvons utiliser des attributs de notre classe afin de maintenir ces
 * structures de données à toutes nos fonctions, mais sans leur donner une portée globale.
 *
 * Aussi, dans une classe, il est plus aisé de définir des méthodes privées auxiliaires qui nous permettent d'alléger
 * l'écriture de nos méthodes publiques.
 *
 * @tparam T
 */
template <typename T>
class ResolveurDijkstra {

    /**
     * Type public servant à transmettre les résultats de l'algorithme.
     */
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
