#include <iostream>
#include <iomanip>

int main()
{
	int choice;
	int numberOfAttempts = 0;

	do 
	{
		std::cout << "Please enter a number between 1-10: ";
		std::cin >> choice;
		
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		numberOfAttempts++;


	} while (choice < 1 || 10 < choice || !std::cin.good());

	if (numberOfAttempts > 5)
	{
		std::cout << "You FINALLY entered: " << choice;
	}
	else
	{
		std::cout << "Thank you. You entered: " << choice;
	}

}