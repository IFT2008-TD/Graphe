/**
 * @file Graphe.h
 * @brief Interface de la classe Graphe développée en IFT-2008 en travail dirigé.
 * @author Pascal Charpentier
 *
 */

#ifndef GRAPHE_GRAPHE_H
#define GRAPHE_GRAPHE_H


#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>


template <typename T, typename P>
class Graphe {

public:
    using Cle_t = T ;
    using Poids_t = P ;

    using  Arrivee_t = struct Arrivee_t {
        Cle_t destination ;
        Poids_t poids ;

        explicit Arrivee_t(Cle_t arrivee) : destination(arrivee), poids() {}
        Arrivee_t(Cle_t arrivee, Poids_t poids) : destination(arrivee), poids(poids) {}
    };

    using Arete_t = struct Arete_t {
        Cle_t depart ;
        Arrivee_t arrivee ;

        Arete_t(Cle_t depart, Arrivee_t arrivee) : depart(depart), arrivee(arrivee) {} ;
        Arete_t(Cle_t depart, Cle_t arrivee, Poids_t poids) : depart(depart), arrivee(arrivee, poids) {}
    };

    using  ListeAdjacence_t         = std::unordered_set<Cle_t> ;
    using  ListeAdjacencePonderee_t = std::unordered_map<Cle_t, Poids_t> ;
    using  Graphe_t                 = std::unordered_map<Cle_t, ListeAdjacencePonderee_t> ;

 public:
    explicit Graphe() = default ;

    Graphe (std::initializer_list<Cle_t>) ;

    Graphe(ListeAdjacence_t l) ;

    Graphe (std::initializer_list<Cle_t>, std::initializer_list<Arete_t>) ;

    void ajouterUnSommet(const Cle_t&) ;

    void renommerUnSommet(const Cle_t&, const Cle_t&) ;

    void retirerUnSommet(const T&) ;

    void ajouterUneArete(const T&, const T&, const P&) ;

    void retirerUneArete(const T&, const T&) ;

    bool sommetExiste(const T&) const ;

    bool areteExiste(const T&, const T&) const ;

    size_t degreEntree(const T&) const ;

    size_t  degreSortie(const T&) const ;

    size_t taille () const ;

    ListeAdjacence_t enumererSommetsAPartirDe(const T&) const ;

    ListeAdjacence_t enumererSommetsVers(const T&) const ;

    ListeAdjacence_t enumererSommets () const ;

    Poids_t lirePoids(Cle_t depart, Cle_t destination) const ;

    std::string format () const ;

private:

    Graphe_t listes ;

private:


    bool invariant () const ;


};

/**
 * Constructeur par liste. Construit un graphe avec une liste de sommets, sans aucune arête.
 * @tparam T
 * @param l liste d'initialisation.  Ne peut contenir de doublons, sinon le constructeur plante.
 * @except invalid_argument si des doublons sont présents dans la liste d'intialisation.
 */
template <typename T, typename P>
Graphe<T, P>::Graphe(std::initializer_list<T> l) {
    for (auto sommet: l) ajouterUnSommet(sommet) ;
    assert(invariant()) ;
}

/**
 * Ajoute un sommet au graphe.
 * @tparam T
 * @param cle Nom du sommet à rajouter.
 * @except invalid_argument si le sommet est déjà présent.
 */
template<typename T, typename P>
void Graphe<T, P>::ajouterUnSommet(const T &cle) {
    auto res = listes.insert(std::pair<Cle_t, ListeAdjacencePonderee_t> (cle, ListeAdjacencePonderee_t())) ;
    if (!res.second) throw std::invalid_argument("ajouterUnSommet: sommet dupliqué") ;
    assert(invariant()) ;
}

template<typename T, typename P>
Graphe<T, P>::Graphe(std::initializer_list<T> lsom, std::initializer_list<Arete_t> lar) : Graphe(lsom) {
    for (auto arete: lar) ajouterUneArete(arete.first, arete.second) ;
}

/**
 * Ajoute une nouvelle arête au graphe.
 * @tparam T
 * @param cleDepart Sommet source.
 * @param cleArrivee Sommet arrivée.
 * @except invalid_argument si un des sommets est non-valide
 * @except invalid_argument si l'arête est déjà présente.
 */
template<typename T, typename P>
void Graphe<T, P>::ajouterUneArete(const T &cleDepart, const T &cleArrivee, const P& poids) {
    if (!sommetExiste(cleDepart) || !sommetExiste(cleArrivee)) throw std::invalid_argument("ajouterUneArete: sommet inexistant") ;
    auto res = listes.at(cleDepart).insert({cleArrivee, poids}) ;
    if (!res.second) throw std::invalid_argument("ajouterUneArete: arete dupliquée") ;

    assert(invariant()) ;
}

/**
 * Vérifie l'existence d'un sommet
 * @tparam T
 * @param cle Sommet à vérifier
 * @return true si cle est dans les sommets du graphe.
 */
template<typename T, typename P>
bool Graphe<T, P>::sommetExiste(const T &cle) const {
    return listes.find(cle) != listes.end() ;
}

/**
 * Vérifie l'existence d'une arête
 * @tparam T
 * @param depart Sommet source
 * @param arrivee Sommet destination
 * @return true si une arête existe entre depart et arrivee
 */
template<typename T, typename P>
bool Graphe<T, P>::areteExiste(const T &depart, const T &arrivee) const {
    if (!sommetExiste(depart) || !sommetExiste(arrivee)) throw std::invalid_argument("areteExiste: sommets inexistants") ;
    return listes.at(depart).find(arrivee) != listes.at(depart).end() ;
}

/**
 * Calcule l'arité d'entrée d'un sommet
 * @tparam T
 * @param cle Nom du sommet
 * @return Le nombre d'arêtes se rendant à cle.
 * @except invalid_argument si cle est non valide.
 */
template<typename T, typename P>
size_t Graphe<T, P>::degreEntree(const T &cle) const {
    return enumererSommetsVers(cle).size() ;
}

/**
 * Calcule l'arité de sortie d'un sommet
 * @tparam T
 * @param cle Nom du sommet
 * @return Le nombre d'arêtes sortant de cle
 * @except invalid_argument si cle est absent du graphe.
 */
template<typename T, typename P>
size_t Graphe<T, P>::degreSortie(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("degreSortie: sommet inexistant") ;
    return listes.at(cle).size() ;
}

/**
 * Calcule le nombre de sommets du graphe.
 * @tparam T
 * @return Le nombre de sommets
 */
template<typename T, typename P>
size_t Graphe<T, P>::taille() const {
    return listes.size() ;
}

/**
 * Énumère les sommets possédant une arête partant d'une source donnée.
 * @tparam T
 * @param cle Le sommet source.
 * @return Les sommets ayant une arête partant de source.
 * @except invalid_argument si cle est non valide.
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacence_t Graphe<T, P>::enumererSommetsAPartirDe(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("enumererSommetsAPartirDe: sommet inexistant") ;

    auto listePonderee = listes.at(cle) ;
    ListeAdjacence_t liste ;

    for (const auto& elem: listePonderee) liste.insert(elem.first) ;
    return liste ;
}

/**
 * énumère les sommets possédant une arête se rendant à une destination
 * @tparam T
 * @param cle Le sommet destination
 * @return Les sommets ayant une arête se rendant à destination
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacence_t Graphe<T, P>::enumererSommetsVers(const T &cle) const {
    if (!sommetExiste(cle)) throw std::invalid_argument("enumererSommetsVers: sommet inexistant") ;
    ListeAdjacence_t resultat ;
    for (const auto& liste: listes) if (liste.second.find(cle) != liste.second.end()) resultat.insert(liste.first) ;
    return resultat ;
}

/**
 * NON IMPLANTÉ: représentation textuelle du graphe
 * @tparam T
 * @return
 */
template<typename T, typename P>
std::string Graphe<T, P>::format() const {
    return std::string();
}

/**
 * Enlever une arête du graphe.  Les sommets sont par ailleurs inchangés.
 * @tparam T
 * @param depart sommet départ de l'arête
 * @param arrivee sommet destination de l'arête
 * @except invalid_argument si l'arête n'existe pas ou si un sommet est non valide.
 */
template<typename T, typename P>
void Graphe<T, P>::retirerUneArete(const T &depart, const T &arrivee) {
    if (!areteExiste(depart, arrivee)) throw std::invalid_argument("retirerUneArete: arète inexistante") ;
    listes.at(depart).erase(arrivee) ;
    assert(invariant()) ;
}

/**
 * Enlève un sommet du graphe.  Enlève aussi toutes les arêtes à départ ou destination de ce sommet.
 * @tparam T
 * @param depart Sommet à retirer
 * @except invalid_argument si depart est non valide.
 */
template<typename T, typename P>
void Graphe<T, P>::retirerUnSommet(const T &depart) {
    for (auto& liste: listes) {
        auto it = liste.second.find(depart) ;
        if (it != liste.second.end())  liste.second.erase(it) ;
    }
    listes.erase(depart) ;

    assert(invariant()) ;
}

/**
 * Change la clé associée à un sommet.  Le graphe est par ailleurs structurellement inchangé.
 * @tparam T
 * @param ancienneCle Ancienne clé du sommet
 * @param nouvelleCle Nouvelle clé du sommet
 * @except invalid_argument si l'ancienne clé n'existe pas, ou si la nouvelle clé est déjà présente.
 */
template<typename T, typename P>
void Graphe<T, P>::renommerUnSommet(const T &ancienneCle, const T& nouvelleCle) {
    if (!sommetExiste(ancienneCle)) throw std::invalid_argument("renommerUnSommet: sommet inexistant") ;
    if (sommetExiste(nouvelleCle)) throw std::invalid_argument("renommerUnSommet: nouveau sommet déjà présent.") ;

    // D'abord on doit remplacer l'ancienne clé dans toutes les listes d'adjacences

    for (auto& liste: listes) {
        auto it = liste.second.find(ancienneCle) ;
        if (it != liste.second.end()) {
            auto poids = it->second ;
            liste.second.erase(it) ;
            liste.second.insert({nouvelleCle, poids}) ;
        }
    }

    // Ensuite recopier la liste d'adjacence associée à l'ancienne clé dans l'entrée de la nouvelle clé
    listes.insert({nouvelleCle, ListeAdjacencePonderee_t (listes.at(ancienneCle).begin(), listes.at(ancienneCle).end())}) ;

    // Puis effacer l'ancienne entrée
    listes.erase(ancienneCle) ;

    assert(invariant()) ;
}

/**
 * Invariant de la classe graphe: tous les sommets destinations doivent être eux-mêmes des sommets valides.
 * @tparam T
 * @return true si le graphe est valide.
 */
template<typename T, typename P>
bool Graphe<T, P>::invariant() const {
    for (auto sommet: listes) {
        for (auto destination: sommet.second) if (!sommetExiste(destination.first)) return false ;
    }
    return true;
}

/**
 * Énumère tous les sommets du graphe.
 * @tparam T
 * @return Une liste des sommets.
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacence_t Graphe<T, P>::enumererSommets() const {
    ListeAdjacence_t resultat ;
    for (const auto& e: listes) resultat.insert(e.first) ;
    return resultat ;
}

template<typename T, typename P>
Graphe<T, P>::Graphe(Graphe::ListeAdjacence_t l) {
   for (auto sommet: l) ajouterUnSommet(sommet) ;
}

template<typename T, typename P>
typename Graphe<T, P>::Poids_t Graphe<T, P>::lirePoids(T depart, T destination) const {
    return listes.at(depart).at(destination) ;
}


#endif //GRAPHE_GRAPHE_H
