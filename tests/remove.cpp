#include "../include/BinarySearchTree.h"
#include "catch.hpp"

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
		BinarySearchTree<int> tree1{10,5,15,2,7,6,1};
		BinarySearchTree<int> tree2{10,6,7,15,2,1};
		WHEN("remove")
		{
			tree1.remove(5);
			THEN("Node is destroyed")
			{
				REQUIRE(tree1==tree2);
			}
		}
	}
}

SCENARIO("Node we want to remove - is root")
{
	GIVEN("tree")
	{
		BinarySearchTree<int> tree1{4,2,1,3,5};
		BinarySearchTree<int> tree2{3,2,1,5};
		WHEN("remove")
		{
			tree1.remove(4);
			THEN("root was removed. We have a new root")
			{
				REQUIRE(tree1==tree2);
			}
		}
	}
}

