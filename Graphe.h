//
// Created by Pascal Charpentier on 2022-05-24.
//

#ifndef GRAPHE_GRAPHE_H
#define GRAPHE_GRAPHE_H

#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>


template <typename T>
class Graphe {
public:
    typedef  std::set<T> ListeAdjacence;
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

    ListeAdjacence enumererSommetsArrivee(const T&) const ;

    ListeAdjacence enumererSommetsDepart(const T&) const ;

    std::string format () const ;

private:

    std::vector<T> sommets ;
    std::vector<std::list<size_t>> listes ;

private:

    size_t numeroDeLaCle(const T& cle) ;


};

template <typename T>
Graphe<T>::Graphe() : sommets(), listes() {

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
typename Graphe<T>::ListeAdjacence Graphe<T>::enumererSommetsArrivee(const T &) const {
    return Graphe::ListeAdjacence();
}

template<typename T>
typename Graphe<T>::ListeAdjacence Graphe<T>::enumererSommetsDepart(const T &) const {
    return Graphe::ListeAdjacence();
}

template<typename T>
std::string Graphe<T>::format() const {
    return std::string();
}

/**
 * @brief Retourne l'index correspondant à la clé de sommet demandée
 * @tparam T Type de la clé de sommet
 * @param cle Clé de sommet
 * @return Le numéro de sommet (0 -> N-1).  Retourne N si le sommet est introuvable.
 * @pre Le graphe doit être non-vide.
 */
template<typename T>
size_t Graphe<T>::numeroDeLaCle(const T &cle) {
    assert(!sommets.empty()) ;
    return static_cast<size_t> (std::find(sommets.begin(), sommets.end(), cle) - sommets.begin()) ;
}


#endif //GRAPHE_GRAPHE_H
