/*
* Exercise 3 - Understanding Pointers 2
* 
* Create a program that will ask the user to enter two integers and assign the given values to two
* separate integers.
* Declare an int* variable and assign it to the memory address of the first integer. Now, using only
* the pointer variable, print the value of the first integer and its memory address. Additionally, print
* the value and the memory address of the pointer variable.
* Then, assign the memory address of the second integer to the same pointer variable. Do the
* same thing as before: using only the pointer variable, print the value of the integer, its memory
* address, and the value and memory address of the pointer variable.
* Do the results make sense to you?
*/

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