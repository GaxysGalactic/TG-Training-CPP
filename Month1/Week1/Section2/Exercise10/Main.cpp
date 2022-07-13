#include <iostream>

int main()
{
	std::cout << "Hello! Please enter an alphabetical character: ";
	char character;
	std::cin >> character;

	if (character != 'a' && character != 'e' && character != 'i' && character != 'o' && character != 'u')
	{
		std::cout << "Your character is not a lowercase vowel!" << std::endl;
	}
	else
	{
		std::cout << "Your character is a lowercase vowel..." << std::endl;
	}
}