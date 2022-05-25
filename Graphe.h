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

private:

    std::map<T, std::set<T>> listes ;


};

template <typename T>
Graphe<T>::Graphe() {

}

template <typename T>
Graphe<T>::Graphe(std::initializer_list<T> l) {

}

template<typename T>
void Graphe<T>::ajouterUnSommet(const T &cle) {
    auto res = listes.insert(std::pair<T, std::set<T>> (cle, std::set<T>())) ;
    if (!res.second) throw std::invalid_argument("ajouterUnSommet: sommet inexistant") ;
}

template<typename T>
void Graphe<T>::ajouterUneArete(const T &cleDepart, const T &cleArrivee) {
    if (!sommetExiste(cleDepart) || !sommetExiste(cleArrivee)) throw std::invalid_argument("ajouterUneArete: sommet inexistant") ;
    if (areteExiste(cleDepart, cleArrivee)) throw std::invalid_argument("ajouterUneArete: are deja existante.") ;
    listes.at(cleDepart).insert(cleArrivee) ;
}

template<typename T>
bool Graphe<T>::sommetExiste(const T &cle) const {
    return listes.find(cle) != listes.end() ;
}

template<typename T>
bool Graphe<T>::areteExiste(const T &depart, const T &arrivee) const {
    if (!sommetExiste(depart) || !sommetExiste(arrivee)) throw std::invalid_argument("areteExiste: sommets inexistants") ;
    return listes.at(depart).find(arrivee) != listes.at(depart).end() ;
}

template<typename T>
size_t Graphe<T>::degreEntree(const T &cle) const {
    return enumererSommetsDepart(cle).size() ;
}

template<typename T>
size_t Graphe<T>::degreSortie(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("degreSortie: sommet inexistant") ;
    return listes.at(cle).size() ;
}

template<typename T>
size_t Graphe<T>::taille() const {
    return listes.size() ;
}

template<typename T>
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommetsArrivee(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("enumererSommetsArrivee: sommet inexistant") ;
    return listes.at(cle) ;
}

template<typename T>
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommetsDepart(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("enumererSommetsDepart: sommet inexistant") ;
    listeAdjacence resultat ;
    for (auto liste: listes) if (liste.second.find(cle) != liste.second.end()) resultat.insert(liste.first) ;
    return resultat ;
}

template<typename T>
std::string Graphe<T>::format() const {
    return std::string();
}


#endif //GRAPHE_GRAPHE_H
