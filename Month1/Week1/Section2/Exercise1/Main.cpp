#include <iostream>

int main()
{
	std::cout << "Welcome to THE GAME!" << std::endl;

	std::cout << "WARNING! This game has some pretty heavy stuff. You need to be at least 18 years old to access it." << std::endl;

	std::cout << "Please enter your age:";
	int age;
	std::cin >> age;

	if (age >= 18)
	{
		std::cout << "Great! You can access the game. You will be contacted shortly with a download link, please wait..." << std::endl;
	}
	else 
	{
		std::cout << "Unfortunately, you do not meet the age requirements for our program. Reporting you to the authorities, please wait..." << std::endl;
	}

}