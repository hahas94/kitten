#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include "segment_tree.hpp"

TEST_CASE("Range max query: int data type, power 2 size.") {
    std::vector<int> data {13, -1, 11, 2, 7, 5, 9, 1};
    RangeMaxQuery<int> tree (data);
    REQUIRE (tree.query(0, 8) == 13);
    REQUIRE (tree.query(0, 4) == 13);
    REQUIRE (tree.query(4, 8) == 9);
    REQUIRE (tree.query(5, 7) == 9);
    REQUIRE (tree.query(1, 7) == 11);

    tree.update(0, 1);
    REQUIRE (tree.query(0, 8) == 11);
    tree.update(2, -2);
    REQUIRE (tree.query(2, 6) == 7);
}

TEST_CASE("Range max query: double data type, odd size.") {
    std::vector<double> data {13., -1., 11, 2, 7, 5, 9};
    RangeMaxQuery<double> tree (data);
    REQUIRE (tree.query(0, 7) == 13);
    REQUIRE (tree.query(0, 4) == 13);
    REQUIRE (tree.query(4, 7) == 9);
    REQUIRE (tree.query(5, 7) == 9);
    REQUIRE (tree.query(1, 7) == 11);

    tree.update(0, 1);
    REQUIRE (tree.query(0, 7) == 11);
    tree.update(2, -2);
    REQUIRE (tree.query(2, 6) == 7);
}

TEST_CASE("Range max query: float data type, even size.") {
    std::vector<float> data {13., -1., 11, 2, 7, 5};
    RangeMaxQuery<float> tree (data);
    REQUIRE (tree.query(0, 6) == 13);
    REQUIRE (tree.query(0, 4) == 13);
    REQUIRE (tree.query(4, 6) == 7);
    REQUIRE (tree.query(5, 6) == 5);
    REQUIRE (tree.query(1, 6) == 11);

    tree.update(0, 1);
    REQUIRE (tree.query(0, 6) == 11);
    tree.update(2, -2);
    REQUIRE (tree.query(2, 6) == 7);
}

TEST_CASE("Range min query.") {
    std::vector<float> data {13., -1., 11, 2, 7, 5};
    RangeMinQuery<float> tree (data);
    REQUIRE (tree.query(0, 6) == -1);
    REQUIRE (tree.query(0, 4) == -1);
    REQUIRE (tree.query(4, 6) == 5);
    REQUIRE (tree.query(5, 6) == 5);
    REQUIRE (tree.query(1, 6) == -1);

    tree.update(0, -2);
    REQUIRE (tree.query(0, 6) == -2);
    tree.update(2, -4);
    REQUIRE (tree.query(2, 6) == -4);
}
