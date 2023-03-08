//
// Created by Pascal Charpentier on 2023-03-07.
//

#ifndef GRAPHE_BASE_RESOLVEURDIJKSTRA_IMPLANTATION_H
#define GRAPHE_BASE_RESOLVEURDIJKSTRA_IMPLANTATION_H

#include "ResolveurDijkstra.h"

/**
 * Constructeur: initialise le moteur de résolution Dijkstra en lui fournissant le graphe à analyser.
 * @tparam T
 * @param graphe Objet graphe à analyser.
 */
template<typename T>
ResolveurDijkstra<T>::ResolveurDijkstra(const Graphe<T, double>& graphe) : graphe(graphe), nonResolus(), estResolu(false), distances(), predecesseurs() {

}

/**
 * Prépare le moteur de résolution Dijkstra à appliquer l'algorithme pour un sommet donné de départ.
 * @tparam T
 * @param depart Clé du sommet de départ.
 */
template<typename T>
void ResolveurDijkstra<T>::initResolveur(const T &depart) {
    estResolu = false ;
    for (auto node: graphe.enumererSommets()) nonResolus[node] = std::numeric_limits<double>::infinity() ;
    nonResolus[depart] = 0 ;
    distances.clear() ;
    predecesseurs.clear() ;
}

/**
 * Applique l'algorithme de Dijkstra pour un sommet de départ donné.
 * @tparam T
 * @param depart Clé du sommet de départ.
 */
template<typename T>
void ResolveurDijkstra<T>::resoudre(const T &depart) {
    initResolveur(depart) ;

    while (!nonResolus.empty()) {
        auto courant = trouverProchainNonResolu() ;
        for (auto voisin: graphe.enumererSommetsAPartirDe(courant))
            if (nonResolus.find(voisin) != nonResolus.end()) relaxer(courant, voisin) ;
        distances[courant] = nonResolus.at(courant) ;
        nonResolus.erase(courant) ;
    }
    estResolu = true ;
}

/**
 * Relaxation du noeud arrivée, à partir du noeud départ.  Si la distance est plus courte, le noeud arrivée est mis à jour
 * et son prédecesseur est le noeud départ.
 * @tparam T
 * @param depart Clé du noeud départ
 * @param arrivee Clé du noeud arrivée.
 */
template<typename T>
void ResolveurDijkstra<T>::relaxer(const T &depart, const T &arrivee) {
    double temp = nonResolus.at(depart) + graphe.lirePoids(depart, arrivee) ;
    if (temp < nonResolus.at(arrivee)) {
        nonResolus.at(arrivee) = temp ;
        predecesseurs[arrivee] = depart ;
    }
}

/**
 * Retourne les résultats d'une résolution de Dijkstra pour un sommet donné.
 * @tparam T
 * @return Un struct ResultatsDijkstra contenant les distances et les prédécesseurs pour un sommet départ donné.
 */
template<typename T>
typename ResolveurDijkstra<T>::ResultatsDijkstra ResolveurDijkstra<T>::resultats() const {
    ResultatsDijkstra resultats ;

    if (estResolu) {
        resultats.distances = distances ;
        resultats.predecesseurs = predecesseurs ;
        return resultats ;
    }

    throw std::logic_error("Le graphe n'a pas été résolu!") ;
}

/**
 * Scanne l'ensemble des noeuds non-résolus pour trouver le prochain à être solutionné.  C'est celui dont la distance
 * au noeud de départ est minimal.
 * @tparam T
 * @return La clé du prochain noeud à résoudre.
 */
template<typename T>
T ResolveurDijkstra<T>::trouverProchainNonResolu() const {
    auto it = std::min_element(nonResolus.begin(), nonResolus.end()) ;
    return it->first ;
}

#endif //GRAPHE_BASE_RESOLVEURDIJKSTRA_IMPLANTATION_H
