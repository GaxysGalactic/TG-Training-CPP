#include <iostream>

int main()
{
	std::cout << "Enter a value for number a: ";
	int a;
	std::cin >> a;

	std::cout << "Enter a value for number b: ";
	int b;
	std::cin >> b;

	std::cout << "Enter a value for number c: ";
	int c;
	std::cin >> c;

	if (a % 2 == 1)
	{
		std::cout << "Number a is ODD!" << std::endl;
	}
	else
	{
		std::cout << "Number a is EVEN!" << std::endl;
	}

	if (b % 2 == 1)
	{
		std::cout << "Number b is ODD!" << std::endl;
	}
	else
	{
		std::cout << "Number b is EVEN!" << std::endl;
	}

	if (c % 2 == 1)
	{
		std::cout << "Number c is ODD!" << std::endl;
	}
	else
	{
		std::cout << "Number c is EVEN!" << std::endl;
	}
}