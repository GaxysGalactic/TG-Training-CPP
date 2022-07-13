#include <iostream>

int main()
{
	std::cout << "Please type a number: ";

	int number;
	

	if (std::cin.peek() == '\n')
	{
		std::cout << "WRONG";
	}

	std::cin >> number;
}