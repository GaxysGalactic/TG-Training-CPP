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