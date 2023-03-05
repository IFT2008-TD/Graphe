//
// Created by Pascal Charpentier on 2022-05-24.
//

#include "gtest/gtest.h"
#include "Graphe.h"

class GrapheTest : public ::testing::Test {
protected:
    Graphe<int, int> g_defaut ; 
    Graphe<int, int> g_4 ; 
    Graphe<int, int> g_2 ;

    GrapheTest() : g_defaut(), g_2({1, 2}), g_4({1, 2, 3, 4}) {}
    
    void SetUp () override {

        g_2.ajouterUneArete(1, 2, 11) ;
        
        g_4.ajouterUneArete(1, 2, 11) ;
        g_4.ajouterUneArete(2, 3, 12) ;
        g_4.ajouterUneArete(3, 4, 13) ;
        g_4.ajouterUneArete(4, 1, 14) ;
        
    }
};

TEST_F(GrapheTest, sommet_existe_g2_g4) {
    EXPECT_TRUE(g_2.sommetExiste(1)) ;
    EXPECT_FALSE(g_2.sommetExiste(0)) ;
    EXPECT_TRUE(g_4.sommetExiste(4)) ;
    EXPECT_FALSE(g_4.sommetExiste(22)) ; 
}

TEST_F(GrapheTest, arete_existe_g2) {
    EXPECT_TRUE(g_2.areteExiste(1, 2)) ; 
    EXPECT_FALSE(g_2.areteExiste(2, 1)) ; 
    EXPECT_FALSE(g_2.areteExiste(1, 1)) ; 
}

TEST_F(GrapheTest, arete_existe_g4) {
    EXPECT_TRUE(g_4.areteExiste(1, 2)) ;
    EXPECT_TRUE(g_4.areteExiste(3, 4)) ;
    EXPECT_FALSE(g_4.areteExiste(1, 4)) ;
    EXPECT_FALSE(g_4.areteExiste(2, 4)) ; 
}

TEST_F(GrapheTest, areteExiste_sommet_inexistant_except) {
    EXPECT_THROW(g_2.areteExiste(1, 8), std::invalid_argument) ; 
    EXPECT_THROW(g_4.areteExiste(66, 4), std::invalid_argument) ; 
}

TEST_F(GrapheTest, degreEntree_g2) {
    EXPECT_EQ(1, g_2.degreEntree(2)) ;
    EXPECT_EQ(0, g_2.degreEntree(1)) ; 
}

TEST_F(GrapheTest, degreEntree_g4) {
    EXPECT_EQ(1, g_4.degreEntree(1)) ;
    EXPECT_EQ(1, g_4.degreEntree(2)) ; 
    EXPECT_EQ(1, g_4.degreEntree(3)) ; 
    EXPECT_EQ(1, g_4.degreEntree(4)) ; 
}

TEST_F(GrapheTest, degreSortie_g2) {
    EXPECT_EQ(1, g_2.degreSortie(1)) ;
    EXPECT_EQ(0, g_2.degreSortie(2)) ; 
}

TEST_F(GrapheTest, degreSortie_g4) {
    EXPECT_EQ(1, g_4.degreSortie(1)) ;
    EXPECT_EQ(1, g_4.degreSortie(2)) ;
    EXPECT_EQ(1, g_4.degreSortie(3)) ;
    EXPECT_EQ(1, g_4.degreSortie(4)) ;
}

TEST_F(GrapheTest, degreEntree_sommet_inexistant_throw) {
    EXPECT_THROW(g_2.degreEntree(66), std::invalid_argument) ;
    EXPECT_THROW(g_4.degreEntree(-1), std::invalid_argument) ;
}

TEST_F(GrapheTest, degreSortie_sommet_inexistant_throw) {
    EXPECT_THROW(g_2.degreSortie(44), std::invalid_argument) ;
    EXPECT_THROW(g_4.degreSortie(6), std::invalid_argument) ;
}

TEST_F(GrapheTest, enumererSommetsArrivee_g2) {
    Graphe<int, int>::ListeAdjacence_t attendu {2}, vide ;
    EXPECT_EQ(attendu, g_2.enumererSommetsAPartirDe(1)) ;
    EXPECT_EQ(vide, g_2.enumererSommetsAPartirDe(2)) ;
}

TEST_F(GrapheTest, enumererSommetsArrivee_g4) {
    Graphe<int, int>::ListeAdjacence_t attendu {3} ;
    EXPECT_EQ(attendu, g_4.enumererSommetsAPartirDe(2)) ;
}

TEST_F(GrapheTest, enumererSommetsDeparts_g2_inexistant_throw) {
    EXPECT_THROW(g_2.enumererSommetsVers(26), std::invalid_argument) ;
    EXPECT_THROW(g_4.enumererSommetsVers(0), std::invalid_argument) ;
}

TEST_F(GrapheTest, enumererSommetsArrivee_inexistant_throw) {
    EXPECT_THROW(g_2.enumererSommetsAPartirDe(10), std::invalid_argument) ;
    EXPECT_THROW(g_4.enumererSommetsAPartirDe(-12), std::invalid_argument) ;
}

TEST_F(GrapheTest, enumererSommetsDepart_g4) {
    Graphe<int, int>::ListeAdjacence_t attendu {3} ;
    EXPECT_EQ(attendu, g_4.enumererSommetsVers(4)) ;
}

TEST_F(GrapheTest, enumererSommetsDepart_g2) {
    Graphe<int, int>::ListeAdjacence_t attendu {1}, vide ;
    EXPECT_EQ(attendu, g_2.enumererSommetsVers(2)) ;
    EXPECT_EQ(vide, g_2.enumererSommetsVers(1)) ;
}

TEST_F(GrapheTest, taille) {
    EXPECT_EQ(2, g_2.taille()) ;
    EXPECT_EQ(4, g_4.taille()) ;
}

TEST_F(GrapheTest, ajouterUnSommet_g2) {
    Graphe<int, int>::ListeAdjacence_t vide ;
    g_2.ajouterUnSommet(3) ;
    EXPECT_EQ(3, g_2.taille()) ;
    EXPECT_TRUE(g_2.sommetExiste(3)) ;
    EXPECT_EQ(vide, g_2.enumererSommetsAPartirDe(3)) ;
    EXPECT_EQ(vide, g_2.enumererSommetsVers(3)) ;
    EXPECT_EQ(0, g_2.degreEntree(3)) ;
    EXPECT_EQ(0, g_2.degreSortie(3)) ;
}

TEST_F(GrapheTest, ajouterUneArete_g4) {
    Graphe<int, int>::ListeAdjacence_t arrivee1{2, 3}, arrivee3{4} ;
    Graphe<int, int>::ListeAdjacence_t depart1{4}, depart3{1, 2};
    g_4.ajouterUneArete(1, 3, 1) ;
    EXPECT_EQ(4, g_4.taille()) ;
    EXPECT_EQ(2, g_4.degreSortie(1)) ;
    EXPECT_EQ(1, g_4.degreSortie(2)) ;
    EXPECT_EQ(1, g_4.degreSortie(3)) ;
    EXPECT_EQ(1, g_4.degreSortie(4)) ;
    EXPECT_EQ(2, g_4.degreEntree(3)) ;
    EXPECT_EQ(1, g_4.degreEntree(1)) ;
    EXPECT_EQ(1, g_4.degreEntree(2)) ;
    EXPECT_EQ(1, g_4.degreEntree(4)) ;
    EXPECT_EQ(arrivee1, g_4.enumererSommetsAPartirDe(1)) ;
    EXPECT_EQ(arrivee3, g_4.enumererSommetsAPartirDe(3)) ;
    EXPECT_EQ(depart1, g_4.enumererSommetsVers(1)) ;
    EXPECT_EQ(depart3, g_4.enumererSommetsVers(3)) ;
}

TEST_F(GrapheTest, renommer_un_sommet_existant) {
    g_2.renommerUnSommet(1, 42) ;
    EXPECT_TRUE(g_2.sommetExiste(42)) ;
    EXPECT_FALSE(g_2.sommetExiste(1)) ;
    EXPECT_TRUE(g_2.areteExiste(42, 2)) ;
}

TEST_F(GrapheTest, renommer_un_sommet_inexistant_throw) {
    EXPECT_THROW(g_2.renommerUnSommet(25, 2), std::invalid_argument) ;
}

TEST_F(GrapheTest, renommer_un_sommet_vers_sommet_deja_present_throw) {
    EXPECT_THROW(g_2.renommerUnSommet(1, 2), std::invalid_argument) ;
}

TEST_F(GrapheTest, enumerer_sommets_g_2) {
    Graphe<int, int>::ListeAdjacence_t attendu {1, 2} ;
    EXPECT_EQ(attendu, g_2.enumererSommets()) ;
}

TEST_F(GrapheTest, enumerer_sommets_g_4) {
    Graphe<int, int>::ListeAdjacence_t attendu {1, 2, 3, 4} ;
    EXPECT_EQ(attendu, g_4.enumererSommets()) ;
}

TEST_F(GrapheTest, retirer_une_arete_g_2) {
    g_2.retirerUneArete(1, 2) ;
    EXPECT_FALSE(g_2.areteExiste(1, 2)) ;
}

TEST_F(GrapheTest, retirer_une_arete_g_4) {
    g_4.retirerUneArete(3, 4) ;
    EXPECT_TRUE(g_4.areteExiste(1, 2)) ;
    EXPECT_TRUE(g_4.areteExiste(2, 3)) ;
    EXPECT_TRUE(g_4.areteExiste(4, 1)) ;
    EXPECT_FALSE(g_4.areteExiste(3, 4)) ;
}

TEST_F(GrapheTest, retirer_une_arete_inexistante) {
    EXPECT_THROW(g_4.retirerUneArete(4, 2), std::invalid_argument) ;
}

TEST_F(GrapheTest, retirer_un_sommet_g_2) {
    g_2.retirerUnSommet(1) ;
    Graphe<int, int>::ListeAdjacence_t attendu {2} ;
    EXPECT_EQ(attendu, g_2.enumererSommets()) ;
    EXPECT_FALSE(g_2.sommetExiste(1)) ;
}

TEST_F(GrapheTest, retirerUnSommet_g_4) {
    g_4.retirerUnSommet(3) ;

    Graphe<int, int>::ListeAdjacence_t attendu {1, 2, 4} ;
    EXPECT_EQ(attendu, g_4.enumererSommets()) ;

    EXPECT_TRUE(g_4.enumererSommetsAPartirDe(2).empty()) ;
    EXPECT_TRUE(g_4.enumererSommetsVers(4).empty()) ;


}

TEST_F(GrapheTest, lirePoids_g_4) {
    EXPECT_EQ(14, g_4.lirePoids(4, 1)) ;
}

TEST_F(GrapheTest, lirePoids_g_4_arete_absente) {
    EXPECT_THROW(g_4.lirePoids(1, 4), std::invalid_argument) ;
}
