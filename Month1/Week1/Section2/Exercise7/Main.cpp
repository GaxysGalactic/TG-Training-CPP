#include <iostream>

int main()
{
	enum Weapon
	{
		WeaponRock = 1, WeaponPaper, WeaponScissors
	};

	std::cout << "Welcome to Rock, Paper, Scissors EXTREME!!" << std::endl;

	std::cout << "1 - Rocky Rock" << std::endl;
	std::cout << "2 - Papery Paper" << std::endl;
	std::cout << "3 - Scissory Scissors" << std::endl;

	int choice;
	std::cout << "Choose your EXTREME weapon!" << std::endl;
	std::cin >> choice;

	std::srand(std::time(0));

	int computerChoice = (std::rand() % 3) + 1;

	switch (computerChoice)
	{
		case WeaponRock:
			std::cout << "Computer's Choice: ROCK" << std::endl;
			switch (choice)
			{
				case WeaponRock:
					std::cout << "Your Choice: ROCK" << std::endl;
					std::cout << "Huh...it's a draw..." << std::endl;
					break;
				case WeaponPaper:
					std::cout << "Your Choice: PAPER" << std::endl;
					std::cout << "You win! Congratulations!" << std::endl;
					break;
				case WeaponScissors:
					std::cout << "Your Choice: SCISSORS" << std::endl;
					std::cout << "You lose, better luck next time..." << std::endl;
					break;
				default:
					std::cout << "That's not a weapon, silly! Choose from the options next time." << std::endl;
					break;
			}
			break;
		case WeaponPaper:
			std::cout << "Computer's Choice: PAPER" << std::endl;
			switch (choice)
			{
			case WeaponRock:
				std::cout << "Your Choice: ROCK" << std::endl;
				std::cout << "You lose, better luck next time..." << std::endl;
				break;
			case WeaponPaper:
				std::cout << "Your Choice: PAPER" << std::endl;
				std::cout << "Huh...it's a draw..." << std::endl;
				break;
			case WeaponScissors:
				std::cout << "Your Choice: SCISSORS" << std::endl;
				std::cout << "You win! Congratulations!" << std::endl;
				break;
			default:
				std::cout << "That's not a weapon, silly! Choose from the options next time." << std::endl;
				break;
			}
			break;
		case WeaponScissors:
			std::cout << "Computer's Choice: SCISSORS" << std::endl;
			switch (choice)
			{
			case WeaponRock:
				std::cout << "Your Choice: ROCK" << std::endl;
				std::cout << "You win! Congratulations!" << std::endl;
				break;
			case WeaponPaper:
				std::cout << "Your Choice: PAPER" << std::endl;
				std::cout << "You lose, better luck next time..." << std::endl;
				break;
			case WeaponScissors:
				std::cout << "Your Choice: SCISSORS" << std::endl;
				std::cout << "Huh...it's a draw..." << std::endl;
				break;
			default:
				std::cout << "That's not a weapon, silly! Choose from the options next time." << std::endl;
				break;
			}
			break;
	}



}