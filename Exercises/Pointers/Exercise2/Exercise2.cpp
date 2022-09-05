/*
* Exercise 2 - Understanding Pointers
* Create a program that will ask the user for an integer value. Assign the value to an integer
* variable.
* Then, create an int* variable and assign it to the memory address of the integer variable.
* Ask the user to enter a new value for the variable. Then, using only the pointer variable, change
* the value of the integer variable to the new value.
* Print the resulting value of variable a.
*/

#include <iostream>

int main()
{
	std::cout << "Please enter a value for the variable 'Number': ";
	int Number;
	std::cin >> Number;

	int* NumberPtr = &Number;

	std::cout << "The value of 'Number' is now: " << Number << std::endl;


	std::cout << std::endl;


	std::cout << "Please enter a new value for 'Number': ";
	std::cin >> *NumberPtr;

	std::cout << "The value of 'Number' is now: " << Number << std::endl;


	std::cout << std::endl;


	std::cout << "Fun fact: I didn't have to touch 'Number' directly to change its value! sunglassesemoji";
}