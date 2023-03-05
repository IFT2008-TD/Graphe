//
// Created by Pascal Charpentier on 2023-03-04.
//

#ifndef GRAPHE_BASE_GRAPHE_IMPLANTATION_HPP
#define GRAPHE_BASE_GRAPHE_IMPLANTATION_HPP

#include "Graphe.h"

/**
 * Constructeur par liste d'initialisation.  Construit un graphe contenant des sommets, sans aucune
 * arête.
 * @tparam T
 * @tparam P
 * @param l Liste d'initialisation contenant les clés des sommets à ajouter au graphe.
 */
template <typename T, typename P>
Graphe<T, P>::Graphe(std::initializer_list<Cle_t> l) {
    for (auto e: l) ajouterUnSommet(e) ;
    assert(invariant()) ;
}

/**
 * Ajoute un nouveau sommet sur le graphe. Sa liste d'adjacence est a-priori vide.
 * @tparam T
 * @param cle Clé du nouveau sommet.
 * @except invalid_argument si le sommet est déjà présent dans le graphe
 */
template<typename T, typename P>
void Graphe<T, P>::ajouterUnSommet(const Cle_t &cle) {
    if (sommetExiste(cle)) throw std::invalid_argument("ajouterUnSommet: sommet existe déjà") ;
    sommets.push_back(cle) ;
    listes.emplace_back() ;

    assert(invariant()) ;
}

/**
 * Ajoute une arête entre deux sommets du graphe.
 * @tparam T
 * @param depart Clé de l'arête de départ
 * @param arrivee Clé de l'arête d'arrivée.
 * @except invalid_argument si l'arête existe déjà dans le graphe
 * @except invalid_argument si un des sommets demandés est inexistant.
 */
template<typename T, typename P>
void Graphe<T, P>::ajouterUneArete(const Cle_t &depart, const Cle_t &arrivee, const Poids_t& poids) {
    if (areteExiste(depart, arrivee)) throw std::invalid_argument("ajouterArete: arete existe déjà") ;
    listes.at(numeroDeLaCle(depart)).emplace_back(numeroDeLaCle(arrivee), poids) ;

    assert(invariant()) ;
}

/**
 * Vérifie si un sommet existe dans le graphe
 * @tparam T
 * @param cle Clé du sommet à rechercher
 * @return true si cle est dans le graphe.
 */
template<typename T, typename P>
bool Graphe<T, P>::sommetExiste(const T &cle) const {
    return numeroDeSommetExiste(numeroDeLaCle(cle)) ;
}

/**
 * Vérifie l'existence d'une arête dans le graphe.
 * @tparam T
 * @param depart Clé du sommet de départ de l'arête
 * @param arrivee Clé du sommet d'arrivée de l'arête
 * @return true si une arête existe entre depart et arrivee
 * @except invalid_argument si un des deux sommets est inexistant
 */
template<typename T, typename P>
bool Graphe<T, P>::areteExiste(const T &depart, const T &arrivee) const {
    size_t idxDepart = numeroDeLaCle(depart) ;
    size_t idxDestination = numeroDeLaCle(arrivee) ;
    if (!numeroDeSommetExiste(idxDepart) || !numeroDeSommetExiste(idxDestination)) throw std::invalid_argument("areteExiste: sommets non valides") ;

    for (auto destination: listes.at(idxDepart))
        if (destination.destination == idxDestination) return true ;
    return false ;
}

/**
 * Dénombre les arêtes aboutissant à un sommet donné
 * @tparam T
 * @param arrivee Sommet de destination des arêtes
 * @return le nombre d'arêtes terminant sur destination
 */
template<typename T, typename P>
size_t Graphe<T, P>::degreEntree(const T &arrivee) const {
    return enumererSommetsVers(arrivee).size() ;
}

/**
 * Dénombre les arêtes partant d'un sommet donné
 * @tparam T
 * @param source Sommet de départ
 * @return le nombre d'arêtes issues de source
 */
template<typename T, typename P>
size_t Graphe<T, P>::degreSortie(const T &source) const {
    return enumererSommetsAPartirDe(source).size() ;
}

/**
 * Dénombre les sommets d'un graphe
 * @tparam T
 * @return Le nombre de sommets dans le graphe
 */
template<typename T, typename P>
size_t Graphe<T, P>::taille() const {
    return sommets.size();
}

/**
 * Énumère les sommets adjacents à un sommet source
 * @tparam T
 * @param source Sommet source
 * @return La liste des sommets vers lesquels source possède une arête
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacence_t Graphe<T, P>::enumererSommetsAPartirDe(const Cle_t &source) const {
    size_t idxSource = numeroDeLaCle(source) ;
    if (!numeroDeSommetExiste(idxSource)) throw std::invalid_argument("enumererSommetsPartantDe: source inexistante") ;

    ListeAdjacence_t resultat ;

    for (const auto& arrivee: listes.at(idxSource)) resultat.insert(sommets.at(arrivee.destination)) ;
    return resultat ;
}

/**
 * Énumère les sommets ayant une arête vers un sommet destination
 * @tparam T
 * @param arrivee Sommet destination
 * @return La listes des sommets ayant une arête vers destination
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacence_t Graphe<T, P>::enumererSommetsVers(const Cle_t &arrivee) const {
    ListeAdjacence_t resultat ;

    for (auto source: sommets)
        if (areteExiste(source, arrivee)) resultat.insert(sommets.at(numeroDeLaCle(source))) ;
    return resultat ;
}

/**
 * Non implantée. Représentation textuelle d'un graphe
 * @tparam T
 * @return un objet string représentant le graphe
 */
template<typename T, typename P>
std::string Graphe<T, P>::format() const {
    return std::string();
}

/**
 * @brief Retourne l'index correspondant à la clé de sommet demandée
 * @tparam T Type de la clé de sommet
 * @param cle Clé de sommet
 * @return Le numéro de sommet (0 -> N-1).  Retourne N si le sommet est introuvable.
 * @pre Le graphe doit être non-vide.
 */
template<typename T, typename P>
size_t Graphe<T, P>::numeroDeLaCle(const Cle_t &cle) const {
    return static_cast<size_t> (std::find(sommets.begin(), sommets.end(), cle) - sommets.begin()) ;
}

/**
 * Vérifie qu'un numéro de sommet est valide.  Ce numéro étant non-signé il est toujours supérieur à 0.
 * Mais il doit aussi être inférieur au nombre de sommets dans la liste des sommets.
 * @tparam T
 * @tparam P
 * @param n Numéro de sommet à vérifier
 * @return true si le numéro de sommet à vérifier est valide.
 */
template<typename T, typename P>
bool Graphe<T, P>::numeroDeSommetExiste(size_t n) const {
    return n < sommets.size() ;
}

/**
 * Change la clé d'un sommet déjà présent.
 * @tparam T
 * @tparam P
 * @param ancienne Clé à modifier
 * @param nouvelle Nouvelle clé à utiliser
 * @except invalid_argument si l'ancienne clé est introuvable, ou si la nouvelle clé est déjà présente.
 */
template<typename T, typename P>
void Graphe<T, P>::renommerUnSommet(const Cle_t &ancienne, const Cle_t &nouvelle) {
    auto n = numeroDeLaCle(ancienne) ;
    if (!numeroDeSommetExiste(n)) throw std::invalid_argument("renommerUnSommet: clé inexistante.") ;
    if (sommetExiste(nouvelle)) throw std::invalid_argument("renommerUnSommet: nouvelle clé existante") ;
    sommets.at(n) = nouvelle ;

    assert(invariant()) ;
}

/**
 * Énumère les clés des sommets du graphe.
 * @tparam T
 * @tparam P
 * @return Un unordered_set contenant les clés de chaque sommet.
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacence_t Graphe<T, P>::enumererSommets() const {
    return Graphe::ListeAdjacence_t(sommets.begin(), sommets.end()) ;
}

/**
 * Élimine une arête du graphe.
 * @tparam T
 * @tparam P
 * @param source Sommet de départ de l'arête à retirer
 * @param arrivee Sommet d'arrivée de l'arête à retirer
 * @except invalid_argument si un sommet est inexistant ou si l'arête n'existe pas.
 */
template<typename T, typename P>
void Graphe<T, P>::retirerUneArete(const T &source, const T &arrivee) {
    if (!areteExiste(source, arrivee)) throw std::invalid_argument("retirerUneArete: arete inexistante") ;

    auto& liste = listes.at(numeroDeLaCle(source)) ;
    auto idxArrivee = numeroDeLaCle(arrivee) ;

    for (auto it = liste.begin(); it != liste.end(); ++it)
        if (it->destination == idxArrivee) {
            liste.erase(it) ;
            return ;
        }

    assert(invariant()) ;
}

/**
 * Élimine le sommet indiqué du graphe. Toutes les arêtes partant de ce sommet ou
 * arrivant à ce sommet seront aussi éliminées.
 * @tparam T
 * @tparam P
 * @param sommet Clé du sommet à éliminer
 * @except invalid_argument si la clé demandée est absente.
 */
template<typename T, typename P>
void Graphe<T, P>::retirerUnSommet(const T &sommet) {



    auto it = std::find(sommets.begin(), sommets.end(), sommet) ;
    if (it == sommets.end()) throw std::invalid_argument("retirerUnSommet: sommet inexistant") ;
    sommets.erase(it) ;

    auto idxSommet = numeroDeLaCle(sommet) ;
    listes.erase(listes.begin() + idxSommet) ;

    for (auto& liste: listes)
        for (auto itt = liste.begin(); itt != liste.end(); ++itt)
            if (itt->destination == idxSommet) {
                liste.erase(itt) ;
                break ;
            }

    for (auto& liste: listes)
        for (auto& dest: liste)
            if (dest.destination > idxSommet)  -- dest.destination ;

    assert(invariant()) ;
}

/**
 * Retourne la pondération associée à une arête.
 * @tparam T
 * @tparam P
 * @param depart Clé du sommet de départ
 * @param destination Clé du sommet destination
 * @return La pondération de l'arête depart -> destination
 * @except invalid_argument si l'arête demandée n'existe pas
 * @except runtime_error si on n'a pas trouvé l'arête demandée dans la liste d'adjacence
 */
template<typename T, typename P>
typename Graphe<T, P>::Poids_t Graphe<T, P>::lirePoids(Cle_t depart, Cle_t destination) const {
    auto idxDepart = numeroDeLaCle(depart) ;
    auto idxArrivee = numeroDeLaCle(destination) ;

    if (!areteExiste(depart, destination)) throw std::invalid_argument("lirePoids: arete inexistante") ;
    auto& liste = listes.at(idxDepart) ;
    for (auto dest: liste)
        if (dest.destination == idxArrivee) return dest.poids ;
    throw std::runtime_error("lirePoids: arete non trouvée") ;
}

/**
 * Vérifie les conditions de validité de l'objet Graphe:
 * 1. Il y a autant de sommets que de listes d'adjacences
 * 2. Chaque sommet est unique
 * 3. Les éléments des listes d'adjacence sont tous des numéros valides de sommets
 * 4. Les éléments des listes d'adjacence sont uniques.
 * @tparam T
 * @tparam P
 * @return true si l'objet est valide.
 */
template<typename T, typename P>
bool Graphe<T, P>::invariant() const {
    ListeAdjacence_t unique_sommets(sommets.begin(), sommets.end()) ;
    if (unique_sommets.size() != sommets.size()) return false ;

    if (sommets.size() != listes.size()) return false ;

    for (auto liste: listes) {
        ListeAdjacence_t adj_unique ;
        for (auto dest: liste) {
            if (!numeroDeSommetExiste(dest.destination)) return false ;
            adj_unique.insert(dest.destination) ;
        }
        if (adj_unique.size() != liste.size()) return false ;
    }
    return true ;
}

/**
 * Retourne un dictionnaire des noeuds adjacents à un sommet donné, et le poids de l'arête.
 * @tparam T
 * @tparam P
 * @param cle La clé du sommet de départ
 * @return Un dictionnaire <cle, poids> contenant les clés adjacentes et le poids des arêtes respectives.
 * @except invalid_argument si le sommet de départ est inexistant dans le graphe.
 */
template<typename T, typename P>
typename Graphe<T, P>::ListeAdjacencePonderee_t Graphe<T, P>::enumererSommetsEtPoidsAPartirDe(const Cle_t& cle) const {
    auto idxCle = numeroDeLaCle(cle) ;
    if (idxCle == taille()) throw std::invalid_argument("enumererSommetsEtPoidsAPartirde: sommet inexistant") ;

    auto& liste = listes.at(idxCle) ;
    return Graphe::ListeAdjacencePonderee_t(liste.cbegin(), liste.cend()) ;
}


#endif //GRAPHE_BASE_GRAPHE_IMPLANTATION_HPP
