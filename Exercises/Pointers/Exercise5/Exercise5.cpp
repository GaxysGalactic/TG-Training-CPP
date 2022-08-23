#include <iostream>

int main()
{

	std::cout << "When I use this array: " << std::endl;

	int Array[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int Sum = 0;
	for (int i = 0; i < 10; i++)
	{
		std::cout << Array[i] << " ";
		Sum += Array[i];
	}

	std::cout << std::endl;

	std::cout << "This is the sum when I loop through the array:" << std::endl;
	std::cout << Sum << std::endl;

	std::cout << std::endl;


	int* ArrayPtr = Array;
	Sum = 0;
	for (int i = 0; i < 10; i++)
	{
		Sum += ArrayPtr[i];
	}

	std::cout << "This is the sum when I loop through the array using a pointer:" << std::endl;
	std::cout << Sum << std::endl;

	std::cout << std::endl;

	Sum = 0;
	for (int i = 0; i < 35; i++)
	{
		Sum += ArrayPtr[i];
	}

	std::cout << "This is the sum when I loop through the array using a pointer and out-of-bounds indices:" << std::endl;
	std::cout << Sum << std::endl;


}