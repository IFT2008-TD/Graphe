

set(TEST_SOURCES test_graphe.cpp ${PROJECT_SOURCE_DIR}/Graphe.h)

add_executable(
        test_graphe
        ${TEST_SOURCES}
)

target_include_directories(test_graphe PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        test_graphe
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(test_graphe)