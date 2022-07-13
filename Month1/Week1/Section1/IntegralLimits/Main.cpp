#include <iostream>
#include <climits>

void Log(const char* message)
{
	std::cout << message << std::endl;
}

int main()
{
	Log("Table of integral data type lower and upper limits in c++");
	Log("------------------------------------------------");
	Log("Data Type\tLower Limit\tUpper Limit");
	Log("------------------------------------------------");

	std::cout << "char\t\t" << CHAR_MIN << "\t\t" << CHAR_MAX << std::endl;
	std::cout << "unsigned char\t" << 0 << "\t\t" << UCHAR_MAX << std::endl;
	std::cout << "short\t\t" << SHRT_MIN << "\t\t" << SHRT_MAX << std::endl;
	std::cout << "unsigned short\t" << 0 << "\t\t" << USHRT_MAX << std::endl;
	std::cout << "int\t\t" << INT_MIN << "\t" << INT_MAX << std::endl;
	std::cout << "unsigned int\t" << 0 << "\t\t" << UINT_MAX << std::endl;
	std::cout << "long long\t" << LLONG_MIN << "\t" << LLONG_MAX << std::endl;
	std::cout << "unsigned long long\t" << 0 << "\t" << ULLONG_MAX << std::endl;


	std::cin.get();
}