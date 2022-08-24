#include <iostream>

int main()
{
	int* DynamicIntPtr = new int;

	delete DynamicIntPtr;

	if (DynamicIntPtr)
	{
		std::cout << "This pointer is valid!" << std::endl;
	}
	else
	{
		std::cout << "The pointer is not valid..." << std::endl;
	}

	std::cout << "This is most likely happening because deleting a pointer to dynamic memory does not turn it to zero." << std::endl;
	std::cout << "It still retains the memory address it had before, so it's still 'valid' since it's pointing to something." << std::endl;
}