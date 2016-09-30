#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("size of empty tree is 0") {
    GIVEN("empty tree") {
        BinarySearchTree<int> tree;
        WHEN("size") {
            THEN("size must be 0") {
                REQUIRE(tree.size() == 0);
            }
        }
    }
}
SCENARIO("size of not empty tree isn't 0") {
    GIVEN("not empty tree") {
        BinarySearchTree<int> tree{1, 2, 3};
        WHEN("decide size") {
            THEN("size isn't 0") {
                REQUIRE(tree.size() != 0);
            }
        }
    }
}
SCENARIO("size of constant tree must be equal to size of not constant tree") {
    GIVEN("constant and not constant trees")
    {
        const BinarySearchTree<int> tree1{1, 2, 3};
        BinarySearchTree<int> tree2{4, 5, 6};
        WHEN("compare")
        {
            THEN("sizes are the same")
            {
                REQUIRE(tree1.size() == tree2.size());
            }
        }
    }
}
