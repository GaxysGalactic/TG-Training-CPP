#include <iostream>


int main()
{
	std::cout << "Please enter a number: ";
	int Number;
	std::cin >> Number;

	std::cout << "The value of your number is " << Number << "." << std::endl;

	std::cout << "The memory address where your variable is stored is " << &Number << std::endl;


	std::cout << std::endl;


	std::cout << "Please enter another number: ";
	std::cin >> Number;

	std::cout << "The value of your number is " << Number << "." << std::endl;

	std::cout << "The memory address where your variable is stored is " << &Number << std::endl;


	std::cout << std::endl;


	std::cout << "Please enter one more number: ";
	int AnotherNumber;
	std::cin >> AnotherNumber;

	std::cout << "The value of your number is " << AnotherNumber << "." << std::endl;

	std::cout << "The memory address where your variable is stored is " << &AnotherNumber << std::endl;

}