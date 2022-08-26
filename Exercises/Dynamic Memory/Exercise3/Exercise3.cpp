/*
* Exercise 3 - Dynamic Allocation Dangers: Memory Leaks
* 
* There are dangers when it comes to allocating memory in the heap. One of these dangers i
* memory leaks! When you allocate memory on the heap, you’re promising that you’ll manage
* that memory… which means that your memory will outlive its current scope and so you need to
* free the memory manually. But what happens when you can’t access the memory anymore?
* You won’t be able to deallocate it and you’ll have a memory leak (useless memory that’s not
* available for new allocations)
* Let’s create a couple of functions that will create memory leaks. Create the following functions:
* void MemoryLeak1();
* void MemoryLeak2(int* intPtr);
* The first function should declare an int pointer and initialize it by allocating an int in the heap.
* That’s all the function does.
* The second function takes in an int pointer but does the same thing. It should assign an int
* allocated in the heap to intPtr. That’s all it needs to do.
* In your main function, call the first function. Then, declare an int pointer (initialized to nullptr) and
* pass it into the second function.
* Then, try to think of a way in which you could free any of that allocated memory inside the main
* function. You’ll find that there is no way to do it - you’ve created two memory leaks. These leaks
* will live in memory for as long as the program is running and you won’t be able to store any ne
* dta in those memory locations.
* Print to the console why each of those functions creates a memory leak.
*/

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