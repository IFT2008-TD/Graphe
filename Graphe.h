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

/**
 * Constructeur par défaut: crée un graphe vide.
 * @tparam T
 */
template <typename T>
Graphe<T>::Graphe() : sommets(), listes() {

}

template <typename T>
Graphe<T>::Graphe(std::initializer_list<T> l) {

}

/**
 * Ajoute un nouveau sommet sur le graphe.
 * @tparam T
 * @param cle Clé du nouveau sommet.
 * @except invalid_argument si le sommet est déjà présent dans le graphe
 */
template<typename T>
void Graphe<T>::ajouterUnSommet(const T &cle) {
    if (sommetExiste(cle)) throw std::invalid_argument("ajouterUnSommet: sommet existe déjà") ;
    sommets.push_back(cle) ;
    listes.emplace_back() ;
}

/**
 * Ajoute une arête entre deux sommets du graphe.
 * @tparam T
 * @param depart Clé de l'arête de départ
 * @param arrivee Clé de l'arête d'arrivée.
 * @except invalid_argument si l'arête existe déjà dans le graphe
 * @except invalid_argument si un des sommets demandés est inexistant.
 */
template<typename T>
void Graphe<T>::ajouterUneArete(const T &depart, const T &arrivee) {
    if (areteExiste(depart, arrivee)) throw std::invalid_argument("ajouterArete: arete existe déjà") ;
    listes.at(numeroDeLaCle(depart)).push_back(numeroDeLaCle(arrivee)) ;
}

/**
 * Vérifie si un sommet existe dans le graphe
 * @tparam T
 * @param cle Clé du sommet à rechercher
 * @return true si cle est dans le graphe.
 */
template<typename T>
bool Graphe<T>::sommetExiste(const T &cle) const {
    return !sommets.empty() && (numeroDeLaCle(cle) != sommets.size()) ;
}

/**
 * Vérifie l'existence d'une arête dans le graphe.
 * @tparam T
 * @param depart Sommet de départ de l'arête
 * @param arrivee Sommet d'arrivée de l'arête
 * @return true si une arête existe entre depart et arrivee
 */
template<typename T>
bool Graphe<T>::areteExiste(const T &depart, const T &arrivee) const {
    if (!(sommetExiste(depart)) || !(sommetExiste(arrivee))) throw std::invalid_argument("areteExiste: sommets non valides") ;
    size_t idxDepart = numeroDeLaCle(depart) ;
    return std::find(listes.at(idxDepart).begin(), listes.at(idxDepart).end(), numeroDeLaCle(arrivee)) != listes.at(idxDepart).end();
}

/**
 * Dénombre les arêtes aboutissant à un sommet donné
 * @tparam T
 * @param arrivee Sommet de destination des arêtes
 * @return le nombre d'arêtes terminant sur destination
 */
template<typename T>
size_t Graphe<T>::degreEntree(const T &arrivee) const {
    return enumererSommetsVers(arrivee).size() ;
}

/**
 * Dénombre les arêtes partant d'un sommet donné
 * @tparam T
 * @param source Sommet de départ
 * @return le nombre d'arêtes issues de source
 */
template<typename T>
size_t Graphe<T>::degreSortie(const T &source) const {
    return enumererSommetsPartantDe(source).size() ;
}

/**
 * Dénombre les sommets d'un graphe
 * @tparam T
 * @return Le nombre de sommets dans le graphe
 */
template<typename T>
size_t Graphe<T>::taille() const {
    return sommets.size();
}

/**
 * Énumère les sommets adjacents à un sommet source
 * @tparam T
 * @param source Sommet source
 * @return La liste des sommets vers lesquels source possède une arête
 */
template<typename T>
typename Graphe<T>::ListeAdjacence Graphe<T>::enumererSommetsPartantDe(const T &source) const {
    if (!sommetExiste(source)) throw std::invalid_argument("enumererSommetsPartantDe: source inexistante") ;

    ListeAdjacence resultat ;
    size_t idxSource = numeroDeLaCle(source) ;
    for (auto idxArrivee: listes.at(idxSource)) resultat.insert(sommets.at(idxArrivee)) ;
    return resultat ;
}

/**
 * Énumère les sommets ayant une arête vers un sommet destination
 * @tparam T
 * @param arrivee Sommet destination
 * @return La listes des sommets ayant une arête vers destination
 */
template<typename T>
typename Graphe<T>::ListeAdjacence Graphe<T>::enumererSommetsVers(const T &arrivee) const {
    if (!sommetExiste(arrivee)) throw std::invalid_argument("enumererSommetsVers: arrivée inexistante") ;

    ListeAdjacence resultat ;
    for (auto source: sommets) if (areteExiste(source, arrivee)) resultat.insert(source) ;
    return resultat ;
}

/**
 * Non implantée. Représentation textuelle d'un graphe
 * @tparam T
 * @return un objet string représentant le graphe
 */
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
