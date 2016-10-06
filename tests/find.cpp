#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("pointer returned, if an element is in the tree") 
{
    GIVEN("tree of int") 
    {
        BinarySearchTree<int> tree{1, 4, 5};
        WHEN("find") 
        {
            THEN("pointer isn't nullptr") 
            {
                REQUIRE(*(tree.find(1)) == 1);
                REQUIRE(*(tree.find(4)) == 4);
                REQUIRE(*(tree.find(5)) == 5);
            }
        }
    }
}

SCENARIO("nullptr returned, if an element isn't in the tree") 
{
    GIVEN("tree of int") 
    {
        BinarySearchTree<int> tree{1, 4, 5};
        WHEN("find") 
        {
            THEN("pointer is nullptr") 
            {
                REQUIRE(tree.find(2) == nullptr);
                REQUIRE(tree.find(3) == nullptr);
                REQUIRE(tree.find(6) == nullptr);
            }
        }
    }
}

SCENARIO("method works fro both constant and not constant trees") 
{
    GIVEN("constant and not constant trees") 
    {
        const BinarySearchTree<int> tree1{2, 3, 6};
        BinarySearchTree<int> tree2{1, 4, 5};
        WHEN("find") 
        {
            THEN("return two pointers") 
            {
                REQUIRE(tree1.find(2));
                REQUIRE(tree1.find(3));
                REQUIRE(tree1.find(6));
                REQUIRE(tree2.find(1));
                REQUIRE(tree2.find(4));
                REQUIRE(tree2.find(5));
            }
        }
    }
}
