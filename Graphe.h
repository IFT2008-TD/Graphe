//
// Created by Pascal Charpentier on 2022-05-24.
//

#ifndef GRAPHE_GRAPHE_H
#define GRAPHE_GRAPHE_H

#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>


template <typename T>
class Graphe {
public:
    typedef  std::set<T> listeAdjacence;
 public:
    explicit Graphe() ;

    Graphe (std::initializer_list<T>) ;

    void ajouterUnSommet(const T&) ;

    void ajouterUneArete(const T&, const T&) ;

    bool sommetExiste(const T&) const ;

    bool areteExiste(const T&, const T&) const ;

    size_t degreEntree(const T&) const ;

    size_t  degreSortie(const T&) const ;

    size_t taille () const ;

    listeAdjacence enumererSommetsArrivee(const T&) const ;

    listeAdjacence enumererSommetsDepart(const T&) const ;

    std::string format () const ;


};

template <typename T>
Graphe<T>::Graphe() {

}

template <typename T>
Graphe<T>::Graphe(std::initializer_list<T> l) {

}

template<typename T>
void Graphe<T>::ajouterUnSommet(const T &) {

}

template<typename T>
void Graphe<T>::ajouterUneArete(const T &, const T &) {

}

template<typename T>
bool Graphe<T>::sommetExiste(const T &) const {
    return false;
}

template<typename T>
bool Graphe<T>::areteExiste(const T &, const T &) const {
    return false;
}

template<typename T>
size_t Graphe<T>::degreEntree(const T &) const {
    return 0;
}

template<typename T>
size_t Graphe<T>::degreSortie(const T &) const {
    return 0;
}

template<typename T>
size_t Graphe<T>::taille() const {
    return 0;
}

template<typename T>
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommetsArrivee(const T &) const {
    return Graphe::listeAdjacence();
}

template<typename T>
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommetsDepart(const T &) const {
    return Graphe::listeAdjacence();
}

template<typename T>
std::string Graphe<T>::format() const {
    return std::string();
}


#endif //GRAPHE_GRAPHE_H
