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

    ListeAdjacence enumererSommetsPartantDe(const T&) const ;

    ListeAdjacence enumererSommetsVers(const T&) const ;

    std::string format () const ;

private:

    std::vector<T> sommets ;
    std::vector<std::list<size_t>> listes ;

private:

    size_t numeroDeLaCle(const T& cle) const ;


};

template <typename T>
Graphe<T>::Graphe() : sommets(), listes() {

}

template <typename T>
Graphe<T>::Graphe(std::initializer_list<T> l) {

}

template<typename T>
void Graphe<T>::ajouterUnSommet(const T &cle) {
    if (sommetExiste(cle)) throw std::invalid_argument("ajouterUnSommet: sommet existe déjà") ;
    sommets.push_back(cle) ;
    listes.emplace_back() ;
}

template<typename T>
void Graphe<T>::ajouterUneArete(const T &depart, const T &arrivee) {
    if (areteExiste(depart, arrivee)) throw std::invalid_argument("ajouterArete: arete existe déjà") ;
    listes.at(numeroDeLaCle(depart)).push_back(numeroDeLaCle(arrivee)) ;
}

template<typename T>
bool Graphe<T>::sommetExiste(const T &cle) const {
    return !sommets.empty() && (numeroDeLaCle(cle) != sommets.size()) ;
}

template<typename T>
bool Graphe<T>::areteExiste(const T &depart, const T &arrivee) const {
    if (!(sommetExiste(depart)) || !(sommetExiste(arrivee))) throw std::invalid_argument("areteExiste: sommets non valides") ;
    size_t idxDepart = numeroDeLaCle(depart) ;
    return std::find(listes.at(idxDepart).begin(), listes.at(idxDepart).end(), numeroDeLaCle(arrivee)) != listes.at(idxDepart).end();
}

template<typename T>
size_t Graphe<T>::degreEntree(const T &arrivee) const {
    return enumererSommetsVers(arrivee).size() ;
}

template<typename T>
size_t Graphe<T>::degreSortie(const T &source) const {
    return enumererSommetsPartantDe(source).size() ;
}

template<typename T>
size_t Graphe<T>::taille() const {
    return sommets.size();
}

template<typename T>
typename Graphe<T>::ListeAdjacence Graphe<T>::enumererSommetsPartantDe(const T &source) const {
    if (!sommetExiste(source)) throw std::invalid_argument("enumererSommetsPartantDe: source inexistante") ;

    ListeAdjacence resultat ;
    size_t idxSource = numeroDeLaCle(source) ;
    for (auto idxArrivee: listes.at(idxSource)) resultat.insert(sommets.at(idxArrivee)) ;
    return resultat ;
}

template<typename T>
typename Graphe<T>::ListeAdjacence Graphe<T>::enumererSommetsVers(const T &arrivee) const {
    if (!sommetExiste(arrivee)) throw std::invalid_argument("enumererSommetsVers: arrivée inexistante") ;

    ListeAdjacence resultat ;
    for (auto source: sommets) if (areteExiste(source, arrivee)) resultat.insert(source) ;
    return resultat ;
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
size_t Graphe<T>::numeroDeLaCle(const T &cle) const {
    return static_cast<size_t> (std::find(sommets.begin(), sommets.end(), cle) - sommets.begin()) ;
}


#endif //GRAPHE_GRAPHE_H
