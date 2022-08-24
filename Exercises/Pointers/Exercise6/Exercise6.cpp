#include <iostream>

int main()
{

	std::srand(std::time(0));

	std::cout << "I've looped through the following numbers: " << std::endl;

	int Array[10];

	int* ArrayPtr;

	for (ArrayPtr = Array; ArrayPtr < Array + 10; ArrayPtr++)
	{
		*ArrayPtr = std::rand();
		std::cout << *ArrayPtr << " ";
	}


	std::cout << std::endl;


	std::cout << "The sum of all those numbers is:";

	int Sum = 0;

	for (ArrayPtr = Array + 9; ArrayPtr > Array; ArrayPtr--)
	{
		Sum += *ArrayPtr;
	}

	std::cout << Sum;
}