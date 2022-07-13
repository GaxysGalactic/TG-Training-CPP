#include <iostream>

int main()
{
	enum Job
	{
		JobDarkKnight = 1, JobPaladin, JobGunbreaker, JobWarrior
	};

	std::cout << "Quick! What's your favorite Final Fantasy XIV tank job?" << std::endl;
	std::cout << "1 - Dark Knight" << std::endl;
	std::cout << "2 - Paladin" << std::endl;
	std::cout << "3 - Gunbreaker" << std::endl;
	std::cout << "4 - Warrior" << std::endl;

	int choice;
	std::cin >> choice;
	std::cout << "Your choice: " << choice << std::endl;

	switch (choice) 
	{
		case JobDarkKnight:
			std::cout << "Excellent choice! May your Bloodspiller strike true." << std::endl;
			break;
		case JobPaladin:
			std::cout << "Fantastic choice! May your oath gauge never run out." << std::endl;
			break;
		case JobGunbreaker:
			std::cout << "Great choice! May all your cartridges be full." << std::endl;
			break;
		case JobWarrior:
			std::cout << "Good choice! May your fell cleaves be strong." << std::endl;
			break;
		default:
			std::cout << "That's not a job, silly! Choose one of the options next time!" << std::endl;
			break;
	}
}