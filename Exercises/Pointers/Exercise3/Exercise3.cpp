#include <iostream>

int main()
{
	std::cout << "Please enter a value for variable FirstNumber: ";
	int FirstNumber;
	std::cin >> FirstNumber;

	std::cout << "Please enter a value for variable SecondNumber: ";
	int SecondNumber;
	std::cin >> SecondNumber;

	std::cout << std::endl;

	int* NumberPtr = &FirstNumber;

	std::cout << "Using pointer variable NumberPtr, I've determined that:" << std::endl;

	std::cout << "The value of FirstNumber is " << *NumberPtr << std::endl;

	std::cout << "The memory address of variable FirstNumber is: " << NumberPtr << std::endl;

	std::cout << "The value of variable NumberPtr is " << NumberPtr << std::endl;

	std::cout << "The memory address of variable NumberPtr is " << &NumberPtr << std::endl;

	std::cout << std::endl;

	NumberPtr = &SecondNumber;

	std::cout << "Using the same pointer variable NumberPtr, I've also determined that: " << std::endl;

	std::cout << "The value of SecondNumber is " << *NumberPtr << std::endl;

	std::cout << "The memory address of variable SecondNumber is: " << NumberPtr << std::endl;

	std::cout << "The value of variable NumberPtr is " << NumberPtr << std::endl;

	std::cout << "The memory address of variable NumberPtr is " << &NumberPtr << std::endl;
}