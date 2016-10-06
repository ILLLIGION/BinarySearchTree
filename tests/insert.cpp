
#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("if element is in tree, insert must return false") 
{
    GIVEN("tree")
    {
        BinarySearchTree<int> tree{1, 3, 5};
        WHEN("insert")
        {
            THEN("must be false")
            {
                REQUIRE(!tree.insert(1));
                REQUIRE(!tree.insert(3));
                REQUIRE(!tree.insert(5));
            }
        }
    }
}

SCENARIO("if element is not in tree, insert method must return true") 
{
    GIVEN("tree")
    {
        BinarySearchTree<int> tree{1, 3, 5};
        WHEN("insert")
        {
            THEN("must be truy")
            {
                REQUIRE(tree.insert(0));
                REQUIRE(tree.insert(2));
                REQUIRE(tree.insert(4));
            }
        }
    }
}

SCENARIO("if inserted value is lesser than the value of root, inserted value must be inserted on the left from root") 
{
    GIVEN("two trees")
    {
        BinarySearchTree<int> tree1{1, 3, -1};
        BinarySearchTree<int> tree2{1, 3};
        WHEN("insert value that is lesser than the root value")
        {
            tree2.insert(-1);
            THEN("value must be inserted on the left from the root")
            {
                REQUIRE(tree1 == tree2);
            }
        }
    }
}


SCENARIO("if inserted value is bigger than the value of root, inserted value must be inserted on the right from root") 
{
    GIVEN("two trees")
    {
        BinarySearchTree<int> tree1{1, 2, 5};
        BinarySearchTree<int> tree2{1, 2};
        WHEN("insert element")
        {
            tree2.insert(5);
            THEN("value must be inserted on the right from the root")
            {
                REQUIRE(tree1 == tree2);
            }
        }
    }
}

SCENARIO("if element is (or not) in tree, size must increase by one (or not change)") 
{
    GIVEN("tree, its size")
    {
        BinarySearchTree<int> tree{1, 3, 5, -1};
        size_t size = tree.size();
        WHEN("insert element that is not in the tree")
        {
            tree.insert(2);
            THEN("sizes must increase by one")
            {
                REQUIRE(tree.size() == size + 1);
            }
        }
        WHEN("insert element that is in the tree")
        {
            tree.insert(3);
            THEN("sizes must be equal")
            {
                REQUIRE(tree.size() == size);
            }
        }
    }
}
