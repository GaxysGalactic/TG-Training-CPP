/*
* Exercise 6 - Pointer Arithmetic
* Pointer arithmetic allows you to perform arithmetic operations on pointer types.
* Create a program where you declare an array of 10 integers. Then, declare an int pointer and
* initialize it to the array.
*
* Loop through all of the elements in the array and initialize each entry in the array with a random
* integer. You must use ONLY the pointer to loop through the array. Print each number to the
* console.
* Then, loop through the array BACKWARDS to get the sum of all the elements. Print the sum to
* the console.
*/

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