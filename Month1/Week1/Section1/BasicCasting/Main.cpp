#include <iostream>

int main()
{

	std::cout << "Testing explicit casting in c++" << std::endl;

	std::cout << "Using ‘int a = 4’ and ‘int b = 7’" << std::endl;

	int a = 4;
	int b = 7;

	std::cout << "a / b = " << a / b << std::endl;
	std::cout << "(float)a / b = " << (float)a / b << std::endl;
	std::cout << "a / (float)b = " << a / (float)b << std::endl;

	std::cout << "Testing implicit casting in c++" << std::endl;

	std::cout << "Using ‘int c = 5’ and ‘float d = 6.6’" << std::endl;

	int c = 5;
	float d = 6.6;

	int e = d;
	std::cout << "int e = d outputs: " << e << std::endl;

	float f = c;
	std::cout << "float f = c outputs: " << f << std::endl;

	std::cin.get();
}