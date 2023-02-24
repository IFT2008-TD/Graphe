set(TEST_SOURCES test_graphe.cpp ${PROJECT_SOURCE_DIR}/Graphe.h)

add_executable(
        test_graphe
        ${TEST_SOURCES})

target_include_directories(test_graphe PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        test_graphe
        gtest_main
        gtest
        pthread
)

set(ALGO_TEST_SOURCES test_graphe_algo.cpp ${PROJECT_SOURCE_DIR}/Graphe.h ${PROJECT_SOURCE_DIR}/graphes_algorithmes.h)

add_executable(
        test_graphe_algo
        ${ALGO_TEST_SOURCES})

target_include_directories(test_graphe_algo PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(
        test_graphe_algo
        gtest_main
        gtest
        pthread)

include(GoogleTest)
gtest_discover_tests(test_graphe)
gtest_discover_tests(test_graphe_algo)