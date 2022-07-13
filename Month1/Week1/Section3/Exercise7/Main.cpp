#include <iostream>
#include <iomanip>

bool hasRepeatsOf(int list[], int size, int number)
{
	for (int i = 0; i < size; i++)
	{
		if (list[i] == number) return true;
	}
	return false;
}

bool hasRepeats(int list[], int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (list[i] == list[j]) return true;
		}
	}
	return false;
}

int main()
{
	std::cout << "Welcome to the OMEGA lottery!" << std::endl;


	int lotteryNumbers[5];
	int size = sizeof(lotteryNumbers) / sizeof(lotteryNumbers[0]);
	std::srand(std::time(0));
	do
	{
		for (int i = 0; i < 5; i++)
		{
			lotteryNumbers[i] = std::rand() % 20;
		}
	} while (hasRepeats(lotteryNumbers, size));

	int chosenNumbers[5];
	int number = -1;
	int i;
	for (i = 0; i < 5; i++)
	{
		std::cout << "Please enter entry #" << i+1 << " (1-20): ";
		std::cin >> std::setw(1) >> number;

		while (std::cin.good() == false || (number < 1 || number > 20) || hasRepeatsOf(chosenNumbers, i, number))
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter a valid number. Remember that you can't repeat numbers." << std::endl << std::endl;
			std::cout << "Please enter entry #" << i+1 << " (1-20): ";
			std::cin >> std::setw(1) >> number;
		}
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		chosenNumbers[i] = number;
	}

	std::cout << "Lottery results: ";

	int correct = 0;
	for (int i = 0; i < 5; i++)
	{
		std::cout << lotteryNumbers[i] << " ";
		if (lotteryNumbers[i] == chosenNumbers[i]) correct++;
	}

	int totalEarnings = 10 * correct;
	std::cout << "Your winnings: $" << totalEarnings << std::endl;
}