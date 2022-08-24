#include <iostream>


void IncrementNumber(int* NumberPtr) const
{
	if (NumberPtr)
	{
		(*NumberPtr)++;
	}
}


int main()
{
	int Number = 69;

	int* NumberPtr = nullptr;

	//NumberPtr = &Number;

	IncrementNumber(NumberPtr);

	std::cout << Number;
}