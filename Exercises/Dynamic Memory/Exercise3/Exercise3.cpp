#include <iostream>

void MemoryLeak1()
{
	int* IntPtr = new int;
}

void MemoryLeak2(int* IntPtr)
{
	int* DynamicIntPtr = new int;
	DynamicIntPtr = IntPtr;
}


int main()
{
	MemoryLeak1();
	int Integer = 0;

	int* InnocentLookingPointer = &Integer;
	MemoryLeak2(InnocentLookingPointer);

	std::cout << "Function 1 creates a memory leak because:" << std::endl;
	std::cout << "It allocates a variable in the heap, but there is no way to access it outside the function scope." << std::endl;
	std::cout << "The integer will stay there for the remainder of the program." << std::endl;

	std::cout << std::endl;

	std::cout << "Function 2 creates a memory leak because:" << std::endl;
	std::cout << "It turns the Dynamic Memory pointer inside the function into one that points to the stack." << std::endl;
	std::cout << "However, the allocated memory wasn't freed prior to that, so it is inaccesible. It will remain for the remainder of the program." << std::endl;
}