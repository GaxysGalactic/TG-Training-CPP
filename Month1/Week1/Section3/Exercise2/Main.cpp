#include <iostream>
#include <iomanip>

char getChoice()
{
	char choice;
	std::cin >> choice;

	int currentAttempt = 1;

	while (!std::cin.good() || (choice != 'F' && choice != 'T'))
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		currentAttempt++;

		if (currentAttempt == 2)
		{
			std::cout << "Oops! Looks like you didn't provide a correct input." << std::endl;
		}
		else if (currentAttempt == 3)
		{
			std::cout << "This is your final warning. One more, and you're finished." << std::endl;
		}
		else if (currentAttempt == 4)
		{
			return 'E';
		}
		std::cin >> choice;
	}

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	return choice;
}


int main()
{
	int numberCorrect = 0;

	std::cout << "Final Exam - True or False. Please respond with T (True) or F (False)" << std::endl;

	std::cout << "Q1: We are currently in the 20th Century." << std::endl;
	char choice;
	choice = getChoice();
	if (choice == 'T')
	{
		std::cout << "INCORRECT. Although the year starts with 20, the 1st century starts with 0: 0379 A.D, for example." << std::endl;
	}
	else if (choice == 'F')
	{
		std::cout << "CORRECT! Well done! You didn't fall for the simple trick." << std::endl;
		numberCorrect++;
	}
	else 
	{
		std::cout << "You will now pay for your transgressions. Your final score is 0." << std::endl;
		return 0;
	}

	std::cout << "Q2: White chocolate does not contain cocoa solids." << std::endl;
	choice = getChoice();
	if (choice == 'T')
	{
		std::cout << "CORRECT! White chocolate is made up of cocoa butter, among other things." << std::endl;
		numberCorrect++;
	}
	else if (choice == 'F')
	{
		std::cout << "INCORRECT. It is made primarily using cocoa butter, which is an emulsion." << std::endl;
	}
	else
	{
		std::cout << "You will now pay for your transgressions. Your final score is 0." << std::endl;
		return 0;
	}

	std::cout << "Q3: 1 is a prime number." << std::endl;
	choice = getChoice();
	if (choice == 'T')
	{
		std::cout << "INCORRECT. A prime number needs at least two distinct factors. " << std::endl;
	}
	else if (choice == 'F')
	{
		std::cout << "CORRECT! Due to the definition of prime numbers, 1 does not fall into the category. Interesting... " << std::endl;
		numberCorrect++;
	}
	else
	{
		std::cout << "You will now pay for your transgressions. Your final score is 0." << std::endl;
		return 0;
	}

	float score = numberCorrect * 5.0f / 3.0f;

	std::cout << "You got " << numberCorrect << "/3 correct. Your final grade is: " << score << std::endl;
}