#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("exception occurs if an element is already in the tree")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        WHEN("insert element")
        {
            THEN("elements can't be repeated")
            {
                REQUIRE_THROWS_AS(tree.insert(1), l_error);
            }
        }   
    }    
}
SCENARIO("if element don't exists => return true")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        WHEN("insert element")
        {
            THEN("element was inserted")
            {
                REQUIRE(tree.insert(10));
            }
        }   
    }    
}
SCENARIO("if inserting element < root->value, add it to the left side of root")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{3, 5};
        BinarySearchTree<int> tree2{3, 1, 5};
        WHEN("insert element")
        {
            tree.insert(1);
            THEN("element must be in the root->left")
            {
                REQUIRE(tree == tree2);
            }
        }
    }   
}
SCENARIO("if inserting element > root->value, add it to the right side of root")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{3, 1};
        BinarySearchTree<int> tree2{3, 1, 5};
        WHEN("insert element")
        {
            tree.insert(5);
            THEN("element must be in the root->right")
            {
               REQUIRE(tree == tree2);
            }
        }
    }   
}
SCENARIO("if element doesn't exist, size must increase")
{
    GIVEN("some tree")
    {
        BinarySearchTree<int> tree{1, 3, 5, 7};
        size_t size = tree.size();
        WHEN("insert element")
        {
            tree.insert(8);
            THEN("newSize == sizeBeforeInserting + 1")
            {
                REQUIRE(tree.size() == size + 1);
            }
        }
    }
}
