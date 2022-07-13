#include <iostream>

int main()
{
	std::cout << "Multiples of 10: " << std::endl;
	int sum = 0;
	for (int i = 1; i <= 100; i++)
	{
		if (i % 10 == 0)
		{
			std::cout << i << " ";
			continue;
		}
		sum += i;
	}
	std::cout << std::endl;
	std::cout << "Sum of non-multiples: " << sum << std::endl;
}