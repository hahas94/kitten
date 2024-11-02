#include <catch2/catch_test_macros.hpp>
#include "unionfind.hpp"

// helper function to test move constructor/assignment
UnionFind create_unionfind(){
		UnionFind uf{10};
        uf.join(1, 0);
        uf.join(4, 3);
        uf.join(1, 3);
		return uf;
}

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

TEST_CASE( "copy constructor" ) {
    int n {6};
    UnionFind uf {UnionFind(n)};

    uf.join(2, 3);
    uf.join(1, 5);
    uf.join(1, 2);

    UnionFind uf2 {uf};


    for(int i = 0; i < n; i++){
        REQUIRE(uf.find(i) == uf2.find(i));
    }

    REQUIRE(uf.size() == uf2.size());
}

TEST_CASE( "copy assignment" ) {
    int n {6};
    UnionFind uf {UnionFind(n)};
    UnionFind uf2 {UnionFind(3)};

    uf.join(2, 3);
    uf.join(1, 5);
    uf.join(1, 2);

    uf2 = uf;


    for(int i = 0; i < n; i++){
        REQUIRE(uf.find(i) == uf2.find(i));
    }

    REQUIRE(uf.size() == uf2.size());
}

TEST_CASE( "move constructor" ) {
    UnionFind uf {create_unionfind()};

    REQUIRE(uf.size() == 10);
    REQUIRE(uf.same(0, 1));
    REQUIRE_FALSE(uf.same(5, 1));
}

TEST_CASE( "move assignment" ) {
    UnionFind uf {UnionFind(3)};
    uf = create_unionfind();
    REQUIRE(uf.size() == 10);
    REQUIRE(uf.same(0, 1));
    REQUIRE_FALSE(uf.same(5, 1));
}

TEST_CASE( "join(), same()" ) {
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