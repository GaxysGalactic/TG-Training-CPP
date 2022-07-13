#include <iostream>

int main()
{
	std::cout << "Heyo! What's your name?" << std::endl;
	std::string answer;
	std::cin >> answer;

	std::cout << "Nice to meet you, " << answer << "! What's your age?" << std::endl;

	int age;

	std::cin >> age;

	int days = age * 365;

	std::cout << "Woah! " << answer << ", did you know you are more or less " << days << " days old?" << std::endl;
}