#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("Element isn't found")
{
	GIVEN("Tree")
	{
		BinarySearchTree<int> tree{10,5,15,2,1};
		WHEN("remove")
		{
			THEN("This element mustn't be found")
			{
				REQUIRE(tree.remove(2314532) == 0);
			}
		}
	}
}

SCENARIO("The Node has only left child")
{
	GIVEN("Node with left child")
	{
		BinarySearchTree<int> tree1{10,5,15,2,1};
		BinarySearchTree<int> tree2{10,5,15,1};
		WHEN("remove")
		{
			tree1.remove(2);
			THEN("Left child becomes new Node")
			{
				REQUIRE(tree1==tree2);
			}
		}
	}
}

SCENARIO("The Node has only right child")
{
	GIVEN("Node with right child")
	{
		BinarySearchTree<int> tree1{10,5,15,2,3};
		BinarySearchTree<int> tree2{10,5,15,3};
		WHEN("remove")
		{
			tree1.remove(2);
			THEN("Right child becomes new Node")
			{
				REQUIRE(tree1==tree2);
			}
		}
	}
}

SCENARIO("The Node doesn't have any children")
{
	GIVEN("Node without children")
	{
		BinarySearchTree<int> tree1{10,5,15,2};
		BinarySearchTree<int> tree2{10,5,15};
		WHEN("remove")
		{
			tree1.remove(2);
			THEN("Nide is just destroyed")
			{
				REQUIRE(tree1==tree2);
			}
		}
	}
}

SCENARIO("The Node has two children")
{
	GIVEN("Node with two children")
	{
		BinarySearchTree<int> tree{20, 10, 9, 26, 24, 27, 22, 23, 25, 21, 28};
		BinarySearchTree<int> tree2{20, 10, 9, 26, 27, 22, 23, 25, 21, 28};
		WHEN("remove")
		{
			tree.remove(24);
			THEN("Node is removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
SCENARIO("Node is root")
{
	GIVEN("Root")
	{
		BinarySearchTree<int> tree{4, 2, 1, 3, 5};
		BinarySearchTree<int> tree2{2, 1, 3, 5};
		WHEN("remove")
		{
			tree.remove(4);
			THEN("Node is removed")
			{
				REQUIRE(tree2 == tree);
			}			
		}
	}
}
