#include <iostream>

void Log(const char* message)
{
	std::cout << message << std::endl;
}

int main()
{
	Log("Table of basic data type sizes in c++");
	Log("------------------------------------------------");
	Log("Data type\tSize (bytes)");
	Log("------------------------------------------------");
	
	std::cout << "char\t\t" << sizeof(char) << std::endl;
	std::cout << "short\t\t" << sizeof(short) << std::endl;
	std::cout << "int\t\t" << sizeof(int) << std::endl;
	std::cout << "long\t\t" << sizeof(long) << std::endl;
	std::cout << "long long\t" << sizeof(long long) << std::endl;
	std::cout << "float\t\t" << sizeof(float) << std::endl;
	std::cout << "double\t\t" << sizeof(double) << std::endl;
	std::cout << "long double\t" << sizeof(long double) << std::endl;
	std::cout << "bool\t\t" << sizeof(bool) << std::endl;


	std::cin.get();
}