/**
 * @file graphes_algorithmes.h
 * @author Pascal Charpentier
 * @date 2023-03-04
 * @version 0.1
 */

#ifndef GRAPHE_BASE_GRAPHES_ALGORITHMES_H
#define GRAPHE_BASE_GRAPHES_ALGORITHMES_H

#include "Graphe.h"
#include <stack>
#include <queue>

/**
 * Type servant à passer les informations nécessaires à la fonctions récursive aux_explorer_DFS: celle-ci doit avoir
 * une copie du graphe, la pile des noeuds abandonnés et l'ensemble des noeuds parcourus.
 * @tparam T
 * @tparam P
 */
template <typename T, typename P>
struct ResultatsDFS_t {
    Graphe<T, P>          graphe ;       //!< Le graphe à visiter
    std::stack<T>         accumulateur ; //!< Pile des noeuds abandonnés
    std::unordered_set<T> parcourus ;    //!< Ensemble des noeuds parcourus

    explicit ResultatsDFS_t(Graphe<T, P> graphe) : graphe(graphe) {}
};

/**
 * Exploration en profondeur à partir d'un noeud de départ donné.
 * @tparam T
 * @tparam P
 * @param dfsInfo struct contenant le graphe, la pile des noeuds abandonnés et les noeuds parcourus.
 * @param sommet Sommet de départ.
 */
template <typename T, typename P>
void aux_explorer_DFS(ResultatsDFS_t<T, P>& dfsInfo, const T& sommet) {
    dfsInfo.parcourus.insert(sommet) ;
    for (auto voisin: dfsInfo.graphe.enumererSommetsAPartirDe(sommet))
        if (dfsInfo.parcourus.find(voisin) == dfsInfo.parcourus.end()) aux_explorer_DFS(dfsInfo, voisin) ;
    dfsInfo.accumulateur.push(sommet) ;
}

/**
 * Exploration en profondeur complète d'un graphe.
 * @tparam T
 * @tparam P
 * @param graphe L'objet graphe à explorer.
 * @return La pile des noeuds abandonnés.
 */
template <typename T, typename P>
std::stack<T> explorer_DFS(const Graphe<T, P>& graphe) {
    struct ResultatsDFS_t<T, P> dfsInfo(graphe) ;

    for (auto sommet: graphe.enumererSommets())
        if (dfsInfo.parcourus.find(sommet) == dfsInfo.parcourus.end()) aux_explorer_DFS(dfsInfo, sommet) ;

    return dfsInfo.accumulateur ;
}

/**
 * Construit un graphe ayant les mêmes sommets mais dont toutes les arêtes sont inversées.
 * @tparam T
 * @tparam P
 * @param graphe Objet graphe dont on veut produire l'inverse
 * @return Le graphe inverse
 */
template <typename T, typename P>
Graphe<T, P> construireInverse(const Graphe<T, P>& graphe) {
    Graphe<T, P> inverse(graphe.enumererSommets()) ;

    for (auto depart: graphe.enumererSommets())
        for (auto destination: graphe.enumererSommetsAPartirDe(depart)) inverse.ajouterUneArete(destination, depart, graphe.lirePoids(depart, destination))  ;
    return inverse ;
}

/**
 * Visite en largeur d'un graphe, à partir d'un sommet de départ donné.
 * @tparam T
 * @tparam P
 * @param graphe
 * @param depart
 * @return
 */
template <typename T, typename P>
std::unordered_map<T, T> explorer_BFS(const Graphe<T, P>& graphe, const T& depart) {
    std::unordered_map<T, T> predecesseurs ;
    std::unordered_set<T> parcourus ;

    std::queue<T> attente ;

    parcourus.insert(depart) ;
    attente.push(depart) ;

    while (!attente.empty()) {
        auto courant = attente.front() ;
        attente.pop() ;

        for (auto voisin: graphe.enumererSommetsAPartirDe(courant)) {
            if (parcourus.find(voisin) == parcourus.end()) {
                parcourus.insert(voisin) ;
                predecesseurs.insert({voisin, courant}) ;
                attente.push(voisin) ;
            }
        }
    }
    return predecesseurs ;
}

/**
 * Tri topologique d'un graphe avec l'algorithme de retrait des sommets des notes de cours.
 * @tparam T
 * @tparam P
 * @param graphe Objet graphe dont on veut produire un tri topologique
 * @return Une liste ordonnée des sommets en ordre de précédence.  Remarque: un tri topologique n'est pas nécessairement
 * unique.
 */
template <typename T, typename P>
std::vector<T> tri_topologique(Graphe<T, P> graphe) {
    std::vector<T> tri ;

    std::unordered_map<T, size_t> arites ;
    for (auto sommet: graphe.enumererSommets()) arites.insert({sommet, graphe.degreEntree(sommet)}) ;

    std::queue<T> sources ;
    for (auto sommet: graphe.enumererSommets()) if (arites.at(sommet) == 0) sources.push(sommet) ;

    while (!sources.empty()) {
        auto courant = sources.front() ; sources.pop() ;
        tri.push_back(courant) ;
        for (auto voisin: graphe.enumererSommetsAPartirDe(courant)) {
             -- arites.at(voisin) ;
             if (arites.at(voisin) == 0) sources.push(voisin) ;
        }
    }
    if (tri.size() != graphe.taille()) throw std::logic_error("tri_topologique: le graphe proposé n'est pas acyclique") ;
    return tri ;
}

#endif //GRAPHE_BASE_GRAPHES_ALGORITHMES_H
