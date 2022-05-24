//
// Created by Pascal Charpentier on 2022-05-24.
//

#ifndef GRAPHE_GRAPHE_H
#define GRAPHE_GRAPHE_H

#include <set>
#include <map>
#include <algorithm>
#include <stdexcept>

/*
- Construction : on doit pouvoir construire un graphe contenant un nombre déterminé de sommets, sans arête.  Par-défaut ce constructeur crée un graphe vide, ne contenant aucun sommet ni arête.
- ajouterUnSommet(cle): cette méthode permet d'ajouter un sommet au graphe. Si la clé existe, la méthode doit échouer d'une manière raisonnable.
- ajouterUneArete(cleDepart, cleArrivee): cette méthode permet d'ajouter une arête au graphe, du sommet de départ au sommet d'arrivée. Si l'arête existe, doit échouer.  Si une des clés n'existe pas, doit aussi échouer.
- sommetExiste(cle): cette méthode permet de vérifier la présence d'un sommet ayant une clé donnée.
- areteExiste(cleDepart, cleArrivee): cette méthode permet de vérifier la présence d'une arête de départ vers arrivée.
- degreEntree(cleArrivee): cette méthode compte le nombre d'arêtes terminant sur cleArrivee.
- degreSortie(cleDepart): cette méthode compte le nombre d'arêtes partant de cleDepart.
- taille: cette méthode retourne le nombre de sommets dans le graphe.
- enumererSommetsArrivee(cleDepart): cette méthode retourne une liste de tous les sommets vers lesquels cleDepart possède une arête.
- enumererSommetsDepart(cleArrivee): cette méthode retourne une liste de tous les sommets ayant une arête vers cleArrivee.
*/
template <typename T>
class Graphe {
public:
    typedef  std::set<T> listeAdjacence;
 public:
    explicit Graphe(size_t cardinal = 0) ;

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
Graphe<T>::Graphe(size_t cardinal) {

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
