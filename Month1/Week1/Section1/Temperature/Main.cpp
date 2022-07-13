#include <iostream>

int main()
{
	double f1, c1, c2, f2;

	std::cout << "Temperature in F: " << std::endl;
	std::cin >> f1;

	c1 = (f1 - 32.0) * 5.0 / 9.0;

	std::cout << "Temperature in C: " << c1 <<  std::endl;

	std::cout << "Temperature in C: " << std::endl;
	std::cin >> c2;

	f2 = c2 * 9.0 / 5.0 + 32.0;

	std::cout << "Temperature in F: " << std::endl;
}