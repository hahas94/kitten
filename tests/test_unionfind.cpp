#include <catch2/catch_test_macros.hpp>
#include "unionfind.hpp"

TEST_CASE( "UnionFind::same" ) {
    int n {6};
    UnionFind uf {UnionFind(n)};

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j){REQUIRE(uf.same(i, j));}
            else{REQUIRE_FALSE(uf.same(i, j));}
        }
    }
}

TEST_CASE( "UnionFind::join" ) {
    int n {6};
    UnionFind uf {UnionFind(n)};
    // [{0}, {1}, {2}, {3}, {4}, {5}]

    uf.join(1, 5);
    REQUIRE(uf.same(1, 5));
    // [{0}, {2}, {3}, {4}, {5, 1}]
    
    uf.join(2, 4);
    REQUIRE(uf.same(2, 4));
    // [{0}, {3}, {4, 2}, {5, 1}]

    REQUIRE_FALSE(uf.same(1, 3));
    REQUIRE_FALSE(uf.same(3, 4));
    REQUIRE_FALSE(uf.same(0, 3));
    REQUIRE_FALSE(uf.same(1, 0));

    uf.join(2, 3);
    REQUIRE(uf.same(2, 3));
    REQUIRE(uf.same(3, 4));
    // [{0}, {4, 2, 3}, {5, 1}]

    uf.join(4, 5);
    REQUIRE(uf.same(2, 3));
    REQUIRE(uf.same(3, 4));
    // [{0}, {4, 2, 3, {5, 1}}]

    uf.join(1, 0);
    REQUIRE(uf.same(0, 3));
    REQUIRE(uf.same(2, 0));
    // [{4, 2, 3, {5, 1}, 0}]
}