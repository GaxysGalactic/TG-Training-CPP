#include <iostream>

int main()
{
	std::cout << "Welcome to your final exam. You will be asked three TRUE or FALSE questions, answer like thus:" << std::endl;
	std::cout << "0 - False" << std::endl;
	std::cout << "1 - True" << std::endl;

	int numberCorrect = 0;

	std::cout << "Q1: We are currently in the 20th Century." << std::endl;
	int answer1;
	std::cin >> answer1;
	if (answer1 == 1)
	{
		std::cout << "INCORRECT. Although the year starts with 20, the 1st century starts with 0: 0379 A.D, for example." << std::endl;
	}
	else
	{
		std::cout << "CORRECT! Well done! You didn't fall for the simple trick." << std::endl;
		numberCorrect++;
	}

	std::cout << "Q2: White chocolate does not contain cocoa solids." << std::endl;
	int answer2;
	std::cin >> answer2;
	if (answer2 == 1)
	{
		std::cout << "CORRECT! White chocolate is made up of cocoa butter, among other things." << std::endl;
		numberCorrect++;
	}
	else
	{
		std::cout << "INCORRECT. It is made primarily using cocoa butter, which is an emulsion." << std::endl;
	}

	std::cout << "Q3: 1 is a prime number." << std::endl;
	int answer3;
	std::cin >> answer3;
	if (answer3 == 1)
	{
		std::cout << "INCORRECT. A prime number needs at least two distinct factors. " << std::endl;
	}
	else
	{
		std::cout << "CORRECT! Due to the definition of prime numbers, 1 does not fall into the category. Interesting... " << std::endl;
		numberCorrect++;
	}

	float score = numberCorrect * 5.0f/3.0f;

	std::cout << "You got " << numberCorrect << "/3 correct. Your final grade is: " << score << std::endl;

}