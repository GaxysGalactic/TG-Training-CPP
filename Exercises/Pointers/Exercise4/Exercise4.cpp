#include <iostream>

int main()
{
	int Number = 69;

	std::cout << "The value of my variable is " << Number << std::endl;

	int* FirstPtr = &Number;
	int* SecondPtr = &Number;

	(*FirstPtr)++;
	(*SecondPtr)++;

	std::cout << "The value of my variable after the pointer stuff I did is " << Number << std::endl;
}