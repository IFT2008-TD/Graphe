//
// Created by Pascal Charpentier on 2023-02-22.
//

#ifndef GRAPHE_BASE_GRAPHES_ALGORITHMES_H
#define GRAPHE_BASE_GRAPHES_ALGORITHMES_H

#include "Graphe.h"
#include <stack>
#include <queue>

template <typename T, typename P>
struct ResultatsDFS_t {
    Graphe<T, P> graphe ;
    std::stack<T> accumulateur ;
    std::unordered_set<T> parcourus ;

    explicit ResultatsDFS_t(Graphe<T, P> graphe) : graphe(graphe) {}
};

template <typename T, typename P>
void aux_explorer_DFS(ResultatsDFS_t<T, P>& dfsInfo, const T& sommet) {
    dfsInfo.parcourus.insert(sommet) ;
    for (auto voisin: dfsInfo.graphe.enumererSommetsAPartirDe(sommet))
        if (dfsInfo.parcourus.find(voisin) == dfsInfo.parcourus.end()) aux_explorer_DFS(dfsInfo, voisin) ;
    dfsInfo.accumulateur.push(sommet) ;
}

template <typename T, typename P>
std::stack<T> explorer_DFS(const Graphe<T, P>& graphe) {
    struct ResultatsDFS_t<T, P> dfsInfo(graphe) ;

    for (auto sommet: graphe.enumererSommets())
        if (dfsInfo.parcourus.find(sommet) == dfsInfo.parcourus.end()) aux_explorer_DFS(dfsInfo, sommet) ;

    return dfsInfo.accumulateur ;
}

template <typename T, typename P>
Graphe<T, P> construireInverse(const Graphe<T, P>& graphe) {
    Graphe<T, P> inverse(graphe.enumererSommets()) ;

    for (auto depart: graphe.enumererSommets())
        for (auto destination: graphe.enumererSommetsAPartirDe(depart)) inverse.ajouterUneArete(destination, depart, graphe.lirePoids(depart, destination))  ;
    return inverse ;
}

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
