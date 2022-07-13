#include <iostream>

int main()
{
	int a, b;

	std::cout << "Please enter two numbers: " << std::endl;
	std::cin >> a;
	std::cin >> b;

	std::cout << "Your first number: " << a << std::endl;
	std::cout << "Your second number: " << b << std::endl;

	std::swap(a, b);

	std::cout << "Your first number swapped: " << a << std::endl;
	std::cout << "Your second number swapped: " << b << std::endl;
}