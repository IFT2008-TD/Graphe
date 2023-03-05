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
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

/**
 * @class Cette classe sert à  représenter des graphes pondérés et orientés.
 * @tparam T Type de clé identifiant les sommets du graphe.
 * @tparam P Type de pondération associées à chaque arête du graphe.
 */
template <typename T, typename P>
class Graphe {

public:

    using Cle_t                     = T ; //!< Clés des sommets
    using Poids_t                   = P ; //!< Pondérations des arêtes

    //! Ce type représente un ensemble de sommets
    using  ListeAdjacence_t         = std::unordered_set<Cle_t> ;

    //! Ce type représente un ensemble de paires sommet-pondération
    using  ListeAdjacencePonderee_t = std::unordered_map<Cle_t, Poids_t> ;


public:
    explicit Graphe() = default ;

    Graphe (std::initializer_list<Cle_t>) ;

    explicit Graphe(ListeAdjacence_t l) ;

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

    ListeAdjacencePonderee_t enumererSommetsEtPoidsAPartirDe(const T&) const ;

    Poids_t lirePoids(Cle_t depart, Cle_t destination) const ;

    std::string format () const ;

private:

    /**
     * Ce type sert à peupler les listes d'adjacence: il contient un numéro de destination et une
     * pondération.
     */
    using Arrivee_t = struct Arrivee_t {
        size_t  destination ;
        Poids_t poids ;

        Arrivee_t(size_t destination, Poids_t poids) : destination(destination), poids(poids) {}
    };



    std::vector<Cle_t>                sommets ;
    std::vector<std::list<Arrivee_t>> listes ;

private:

    bool   numeroDeSommetExiste(size_t n) const ;
    size_t numeroDeLaCle(const Cle_t&)    const ;

    bool   invariant ()                   const ;


} ;

#include "Graphe_implantation.hpp"

#endif //GRAPHE_GRAPHE_H
