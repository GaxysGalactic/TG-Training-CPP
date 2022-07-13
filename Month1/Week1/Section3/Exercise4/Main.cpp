#include <iostream>

int main()
{
	std::cout << "Multiples of 10: " << std::endl;
	for (int i = 1; i <= 10; i++)
	{
		int mult = 10 * i;
		std::cout << mult << " ";
	}
}