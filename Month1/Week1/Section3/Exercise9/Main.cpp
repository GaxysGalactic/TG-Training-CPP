#include <iostream>

int main()
{
	char myString[30] = "A string of thirty characters";
	char myReversedString[30];

	int size;
	for (size = 0; myString[size] != '\0'; size++);
	for (int i = 0; i < size; i++)
	{
		myReversedString[size - i - 1] = myString[i];
	}
	myReversedString[size] = '\0';

	std::cout << "My string initialized with double quotes is: " << myString << std::endl;
	std::cout << "My string reversed is: " << myReversedString << std::endl;

	char myNewString[30]{ 'H', 'E', 'L', 'L', 'O', '\0' };
	char myNewReversedString[30];

	for (size = 0; myNewString[size] != '\0'; size++);
	for (int i = 0; i < size; i++)
	{
		myNewReversedString[size - i - 1] = myNewString[i];			
	}
	myNewReversedString[size] = '\0';

	std::cout << "My string initialized with single characters is: " << myNewString << std::endl;
	std::cout << "My string reversed is: " << myNewReversedString << std::endl;

}