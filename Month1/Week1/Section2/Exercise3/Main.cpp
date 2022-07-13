#include <iostream>

int main()
{
	int a;
	std::cout << "Please enter a number: ";
	std::cin >> a;

	if (a == 0)
	{
		std::cout << "Your number is zero!" << std::endl;
	}
	else if (a > 0)
	{
		std::cout << "Your number is positive!" << std::endl;
	}
	else if (a < 0)
	{
		std::cout << "Your number is negative!" << std::endl;
	}
}