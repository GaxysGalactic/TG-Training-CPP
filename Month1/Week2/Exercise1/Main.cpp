#include <iostream>


class FirstClass
{
public:
	FirstClass()
	{
		std::cout << "I am in the constructor!" << std::endl;
	}

	~FirstClass()
	{
		std::cout << "I am in the destructor!" << std::endl;
	}
};


void testOne()
{
	FirstClass fc1;
	FirstClass fc2;
	FirstClass fc3;
	FirstClass fc4;
	FirstClass fc5;
}


void testTwo()
{
	for (int i = 0; i < 5; i++)
	{
		FirstClass f6;
	}
}


int main()
{
	std::cout << "========================" << std::endl;
	std::cout << "Starting test one" << std::endl;
	testOne();

	std::cout << "========================" << std::endl;
	std::cout << "Starting test two" << std::endl;
	testTwo();
}