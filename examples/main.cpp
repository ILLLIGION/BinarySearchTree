#include "../include/BinarySearchTree.h"

int main(int argc, char* argv[])
{
	BinarySearchTree<char> Tree1{ 'q', 'w', 'e', 'r', 't', 'y' };
	std::cout << Tree1 << std::endl;

	BinarySearchTree<double> Tree2{ 2.3, 4.2, 3.2, 5.32 };
	std::cout << Tree2 << std::endl;

	try
	{
		Tree2.insert(2.3);
	}
	catch(l_error& error)
	{
		std::cerr << error.what() << std::endl;
	}
	try
	{
		Tree2.find(100);
	}
	catch (l_error& error)
	{
		std::cerr << error.what() << std::endl;
	}
	try
	{
		Tree2.remove(100);
	}
	catch (l_error& error)
	{
		std::cerr << error.what() << std::endl;
	}
	
	system("pause");
	return 0;
}

