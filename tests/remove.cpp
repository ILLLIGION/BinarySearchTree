#include "../include/BinarySearchTree.h"
#include "catch.hpp"

SCENARIO("Element isn't found => exception")
{
	GIVEN("Tree")
	{
		BinarySearchTree<int> tree{10,5,15,2,1};
		WHEN("remove")
		{
			THEN("This element mustn't be found")
			{
				REQUIRE_THROWS_AS(tree.remove(2314532), l_error);
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
