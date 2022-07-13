#include <iostream>

int main()
{
	std::cout << "In c++, arithmetic follows the PEMDAS rule! Check it out:" << std::endl;

	std::cout << "Enter a value for number a:" << std::endl;
	int a;
	std::cin >> a;

	std::cout << "Enter a value for number b:" << std::endl;
	int b;
	std::cin >> b;
	
	std::cout << "Enter a value for number c:" << std::endl;
	int c;
	std::cin >> c;


	int equation1 = a + 1 * b + 2 - c;
	std::cout << "a + 1 * b + 2 - c	=" << equation1 << std::endl;

	int equation2 = (a + 1) * (b + 2) - c;
	std::cout << "(a + 1) * (b + 2) - c	= " << equation2 << std::endl;
}