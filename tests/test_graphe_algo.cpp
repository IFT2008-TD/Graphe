//
// Created by Pascal Charpentier on 2023-02-23.
//

#include "gtest/gtest.h"
#include "Graphe.h"
#include "graphes_algorithmes.h"

class GrapheEssai : public ::testing::Test {
protected:
    Graphe<int, int> vide ;
    Graphe<int, int> unSommet ;
    Graphe<int, int> deuxSommets ;
    Graphe<int, int> troisSommets ;
    Graphe<int, int> quatreSommets ;

    GrapheEssai() : vide(), unSommet({1}), deuxSommets({1, 2}), troisSommets({1, 2, 3}), quatreSommets({1, 2, 3, 4}) {}

    void SetUp() override {
        deuxSommets.ajouterUneArete(1, 2, 1) ;

        troisSommets.ajouterUneArete(1, 2, 1) ;
        troisSommets.ajouterUneArete(2, 3, 1) ;

        quatreSommets.ajouterUneArete(1, 2, 1) ;
        quatreSommets.ajouterUneArete(2, 3, 1) ;
        quatreSommets.ajouterUneArete(2, 4, 1) ;
    }
};

TEST_F(GrapheEssai, inverse_vide_vide) {
    Graphe<int, int> inverse_vide = construireInverse(vide) ;
    EXPECT_EQ(0, inverse_vide.taille()) ;
}

TEST_F(GrapheEssai, inverse_un_sommet_inchange) {
    Graphe<int, int> inverse_un = construireInverse(unSommet) ;
    EXPECT_EQ(1, inverse_un.taille()) ;
    EXPECT_TRUE(inverse_un.sommetExiste(1)) ;
}

TEST_F(GrapheEssai, inverse_deux_sommets) {
    Graphe<int, int> inverse_deux = construireInverse(deuxSommets) ;
    EXPECT_EQ(2, inverse_deux.taille()) ;
    EXPECT_TRUE(inverse_deux.sommetExiste(1)) ;
    EXPECT_TRUE(inverse_deux.sommetExiste(2)) ;
    EXPECT_TRUE(inverse_deux.areteExiste(2, 1)) ;
    EXPECT_FALSE(inverse_deux.areteExiste(1, 2)) ;
}

TEST_F(GrapheEssai, inverse_trois_sommets) {
    Graphe<int, int> inverse_trois = construireInverse(troisSommets) ;
    EXPECT_EQ(3, inverse_trois.taille()) ;
    EXPECT_TRUE(inverse_trois.sommetExiste(1)) ;
    EXPECT_TRUE(inverse_trois.sommetExiste(2)) ;
    EXPECT_TRUE(inverse_trois.sommetExiste(3)) ;
    EXPECT_TRUE(inverse_trois.areteExiste(3, 2)) ;
    EXPECT_TRUE(inverse_trois.areteExiste(2, 1)) ;
    EXPECT_FALSE(inverse_trois.areteExiste(1, 2)) ;
    EXPECT_FALSE(inverse_trois.areteExiste(2, 3)) ;
    EXPECT_FALSE(inverse_trois.areteExiste(1, 3)) ;
    EXPECT_FALSE(inverse_trois.areteExiste(3, 1)) ;
}

TEST_F(GrapheEssai, explorer_BFS_unSommet_predecesseurs_vide) {
    auto resultat = explorer_BFS(unSommet, 1) ;
    EXPECT_TRUE(resultat.empty()) ;
}

TEST_F(GrapheEssai, explorer_BFS_deuxSommets_1_predecesseur_de_2) {
    auto resultat = explorer_BFS(deuxSommets, 1) ;
    EXPECT_EQ(1, resultat.size()) ;
    EXPECT_EQ(1, resultat.at(2)) ;
}

TEST_F(GrapheEssai, explorer_BFS_troisSommets) {
    auto resultat = explorer_BFS(troisSommets, 1) ;
    EXPECT_EQ(2, resultat.size()) ;
    EXPECT_EQ(1, resultat.at(2)) ;
    EXPECT_EQ(2, resultat.at(3)) ;
}

TEST_F(GrapheEssai, explorer_BFS_quatreSommets) {
    quatreSommets.ajouterUneArete(3, 4, 1) ;
    auto resultat = explorer_BFS(quatreSommets, 1) ;
    EXPECT_EQ(3, resultat.size()) ;
    EXPECT_EQ(1, resultat.at(2)) ;
    EXPECT_EQ(2, resultat.at(3)) ;
    EXPECT_EQ(2, resultat.at(4)) ;
}

TEST_F(GrapheEssai, tri_topologique_graphe_vide) {
    auto resultat = tri_topologique(vide) ;
    EXPECT_TRUE(resultat.empty()) ;
}

TEST_F(GrapheEssai, tri_topologique_un_sommet) {
    std::vector<int> attendu {1} ;
    auto resultat = tri_topologique(unSommet) ;
    EXPECT_EQ(attendu, resultat) ;
}

TEST_F(GrapheEssai, tri_topologique_deux_sommets) {
    std::vector<int> attendu {1, 2} ;
    auto resultat = tri_topologique(deuxSommets) ;
    EXPECT_EQ(attendu, resultat) ;
}

TEST_F(GrapheEssai, tri_topologique_trois_sommets) {
    std::vector<int> attendu {1, 2, 3} ;
    auto resultat = tri_topologique(troisSommets) ;
    EXPECT_EQ(attendu, resultat) ;
}

TEST_F(GrapheEssai, tri_topologique_quatre_sommets) {
    std::vector<int> attendu {1, 2, 3, 4} ;
    auto resultat = tri_topologique(quatreSommets) ;
    EXPECT_EQ(attendu, resultat) ;
}

TEST_F(GrapheEssai, tri_topologique_cycle_throw) {
    troisSommets.ajouterUneArete(3, 1, 1) ;
    EXPECT_THROW(tri_topologique(troisSommets), std::logic_error) ;
}