#include <iostream>


int main()
{
	int* Integer = new int;
	*Integer = 69;

	std::cout << "I've dynamically allocated an integer. Its value is " << *Integer << " and its memory address is " << Integer;

	delete Integer;
}