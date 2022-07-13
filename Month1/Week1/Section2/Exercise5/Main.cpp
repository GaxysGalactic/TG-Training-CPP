#include <iostream>

int main()
{
	std::cout << "Welcome to the Excitraton 6000!" << std::endl;
	std::cout << "1 - Heads" << std::endl;
	std::cout << "2 - Tails" << std::endl;

	std::cout << "What's your guess?" << std::endl;
	int guess;
	std::cin >> guess;

	std::srand(std::time(0));

	if (rand() % 2)
	{
		std::cout << "Actual result: TAILS. ";
		if (guess == 2)
		{
			std::cout << "Your guess: TAILS. " << std::endl;
			std::cout << "You win!" << std::endl;
		}
		else
		{
			std::cout << "Your guess: HEADS. " << std::endl;
			std::cout << "You lose..." << std::endl;
		}
	}
	else
	{
		std::cout << "Actual result: HEADS. ";
		if (guess == 1)
		{
			std::cout << "Your guess: HEADS. " << std::endl;
			std::cout << "You win!" << std::endl;
		}
		else
		{
			std::cout << "Your guess: TAILS. " << std::endl;
			std::cout << "You lose..." << std::endl;
		}

	}
}