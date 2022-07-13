
/*
Exercise 1 - Understanding Classes

Create a class called FirstClass with a public constructor and destructor. Have the constructor output “I’m in the constructor!” and have the destructor output “I’m in the destructor!”. Then, instantiate 5 classes and run your program, are the constructor and destructor calls where you expected them to be?

Now create a loop of at least five iterations. For each iteration, instantiate your class once. Run your program, are the constructor and destructor calls where you expected them to be?

*/


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