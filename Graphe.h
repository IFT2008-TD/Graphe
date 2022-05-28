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
    explicit Graphe() = default ;

    Graphe (std::initializer_list<T>) ;

    void ajouterUnSommet(const T&) ;

    void renommerUnSommet(const T&, const T&) ;

    void retirerUnSommet(const T&) ;

    void ajouterUneArete(const T&, const T&) ;

    void retirerUneArete(const T&, const T&) ;

    bool sommetExiste(const T&) const ;

    bool areteExiste(const T&, const T&) const ;

    size_t degreEntree(const T&) const ;

    size_t  degreSortie(const T&) const ;

    size_t taille () const ;

    listeAdjacence enumererSommetsAPartirDe(const T&) const ;

    listeAdjacence enumererSommetsVers(const T&) const ;

    listeAdjacence enumererSommets () const ;

    std::string format () const ;

private:

    std::map<T, std::set<T>> listes ;

    bool invariant () const ;


};


template <typename T>
Graphe<T>::Graphe(std::initializer_list<T> l) {
    for (auto sommet: l) ajouterUnSommet(sommet) ;
    assert(invariant()) ;
}

template<typename T>
void Graphe<T>::ajouterUnSommet(const T &cle) {
    auto res = listes.insert(std::pair<T, std::set<T>> (cle, std::set<T>())) ;
    if (!res.second) throw std::invalid_argument("ajouterUnSommet: sommet inexistant") ;
    assert(invariant()) ;
}

template<typename T>
void Graphe<T>::ajouterUneArete(const T &cleDepart, const T &cleArrivee) {
    if (!sommetExiste(cleDepart) || !sommetExiste(cleArrivee)) throw std::invalid_argument("ajouterUneArete: sommet inexistant") ;
    if (areteExiste(cleDepart, cleArrivee)) throw std::invalid_argument("ajouterUneArete: are deja existante.") ;
    listes.at(cleDepart).insert(cleArrivee) ;

    assert(invariant()) ;
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
    return enumererSommetsVers(cle).size() ;
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
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommetsAPartirDe(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("enumererSommetsAPartirDe: sommet inexistant") ;
    return listes.at(cle) ;
}

template<typename T>
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommetsVers(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("enumererSommetsVers: sommet inexistant") ;
    listeAdjacence resultat ;
    for (auto liste: listes) if (liste.second.find(cle) != liste.second.end()) resultat.insert(liste.first) ;
    return resultat ;
}

template<typename T>
std::string Graphe<T>::format() const {
    return std::string();
}

template<typename T>
void Graphe<T>::retirerUneArete(const T &depart, const T &arrivee) {
    if (!areteExiste(depart, arrivee)) throw std::invalid_argument("retirerUneArete: arète inexistante") ;
    listes.at(depart).erase(arrivee) ;
    assert(invariant()) ;
}

template<typename T>
void Graphe<T>::retirerUnSommet(const T &depart) {
    for (auto liste: listes) {
        auto it = liste.second.find(depart) ;
        if (it != liste.second.end())  liste.second.erase(it) ;
    }
    listes.erase(depart) ;

    assert(invariant()) ;
}

template<typename T>
void Graphe<T>::renommerUnSommet(const T &ancienneCle, const T& nouvelleCle) {
    if (!sommetExiste(ancienneCle)) throw std::invalid_argument("renommerUnSommet: sommet inexistant") ;

    for (auto liste: listes) {
        auto it = liste.second.find(ancienneCle) ;
        if (it != liste.second.end()) {
            liste.second.erase(it) ;
            liste.second.insert(nouvelleCle) ;
        }
    }

    listes.insert({nouvelleCle, std::set<T> (listes.at(ancienneCle).begin(), listes.at(ancienneCle).end())}) ;
    listes.erase(ancienneCle) ;
    assert(invariant()) ;
}

template<typename T>
bool Graphe<T>::invariant() const {
    for (auto sommet: listes) {
        for (auto destination: sommet.second) if (!sommetExiste(destination)) return false ;
    }
    return true;
}

template<typename T>
typename Graphe<T>::listeAdjacence Graphe<T>::enumererSommets() const {
    listeAdjacence resultat ;
    for (auto e: listes) resultat.insert(e.first) ;
    return resultat ;
}


#endif //GRAPHE_GRAPHE_H
