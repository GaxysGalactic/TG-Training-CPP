#include <iostream>
#include <iomanip>


int main()
{
	int myFirstArray[10];
	int number = -1;

	

	int i = 0;
	int sum = 0;

	do
	{
		std::cout << "Enter a number if you want: ";
		std::cin >> number;

		if (!std::cin.good()) break;

		myFirstArray[i] = number;
		sum += number;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		i++;
	} while (i < 10);

	if (i == 10)
		std::cout << "I didn't account for this. Array is now full :c" << std::endl;

	std::cout << "Total numbers entered: " << i << std::endl;
	std::cout << "Total sum of numbers entered: " << sum << std::endl;


}