#include <iostream>
#include <climits>

int main()
{

	std::cout << "Sometimes overflow and underflow can happen if we’re not careful with our data sizes and values!" << std::endl;

	int a = INT_MAX;
	int aplus = a + 1;

	std::cout << "Overflow can happen when we evaluate " << a << " + 1. The resulting value will be :" << aplus << std::endl;

	int b = INT_MIN;
	int bminus = b - 1;

	std::cout << "Underflow can happen when we evaluate " << b << " - 1. The resulting value will be :" << bminus << std::endl;


	std::cin.get();
}