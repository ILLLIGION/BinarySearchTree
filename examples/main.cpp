#include "BinarySearchTree.h"

	int main(int argc, char* argv[])
	{
		BinarySearchTree<char> Tree1{ 'q', 'w', 'e', 'r', 't', 'y' };
		std::cout << Tree1 << std::endl;

		BinarySearchTree<double> Tree2{ 2.3, 4.2, 3.2, 5.32 };
		std::cout << Tree2 << std::endl;

		return 0;
	}
