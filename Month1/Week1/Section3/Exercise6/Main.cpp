#include <iostream>
#include <iomanip>

int main()
{
	int myBetterArray[10];
	int number;

	int sum = 0;
	int i;
	for (i = 0; i < 10; i++)
	{
		std::cout << "Enter a number if you want or press ENTER to finish: ";

		if (std::cin.peek() == '\n') break;
		std::cin >> number;

		bool enterPressedDuringValidation = false;
		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter a valid number or press ENTER to finish!" << std::endl << std::endl;
			std::cout << "Enter a number if you want or press ENTER to finish: ";
			std::cin >> number;
			if (std::cin.peek() == '\n')
			{
				enterPressedDuringValidation = true;
				break;
			}
		}
		if (enterPressedDuringValidation) break;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		myBetterArray[i] = number;
		sum += number;
	}
	if (i == 10)
		std::cout << "I didn't account for this. Array is now full :c" << std::endl;

	std::cout << "Total numbers entered: " << i << std::endl;
	std::cout << "Total sum of numbers entered: " << sum << std::endl;


}