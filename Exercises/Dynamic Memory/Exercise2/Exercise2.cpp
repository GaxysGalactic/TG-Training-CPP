/*
* Exercise 2 - Understanding Stack vs Heap
* Let’s compare the memory addresses of the stack and the heap.
* First, create three int variables called stackInt1, stackInt2, and stackInt3. These variables should
* be allocated in the stack. Initialize them to whatever value you want and then print their value
* and memory addresses.
* Then, create three more int variables and call them healpInt1, heapInt2, and heapInt3. These
* variables should be allocated in the heap. Initialize them to whatever value you want and print
* their value and memory addresses.
* What can you notice from the memory addresses in the stack vs the memory addresses in the
* heap? Print the answer to that question to the console (Yep, we’re doing quizzes in exercises
* now).
*/

#include <iostream>

int main()
{
	const int StackInt1 = 204;
	const int StackInt2 = 36;
	const int StackInt3 = 777;

	std::cout << "I created three stack variables." << std::endl;

	std::cout << "Their values are: " << std::endl;

	std::cout << StackInt1 << std::endl;
	std::cout << StackInt2 << std::endl;
	std::cout << StackInt3 << std::endl;

	std::cout << "Their memory addresses are: " << std::endl;

	std::cout << &StackInt1 << std::endl;
	std::cout << &StackInt2 << std::endl;
	std::cout << &StackInt3 << std::endl;


	std::cout << std::endl;


	int* HeapInt1 = new int;
	int* HeapInt2 = new int;
	int* HeapInt3 = new int;

	*HeapInt1 = 24;
	*HeapInt2 = 42;
	*HeapInt3 = 21;

	std::cout << "I created three heap variables." << std::endl;

	std::cout << "Their values are: " << std::endl;

	std::cout << *HeapInt1 << std::endl;
	std::cout << *HeapInt2 << std::endl;
	std::cout << *HeapInt3 << std::endl;

	std::cout << "Their memory addresses are: " << std::endl;

	std::cout << HeapInt1 << std::endl;
	std::cout << HeapInt2 << std::endl;
	std::cout << HeapInt3 << std::endl;


	std::cout << std::endl;

	/*
	* Q1
	* What can you notice from the memory addresses in the stack vs the memory addresses in the
	* heap?
	*/

	std::cout << "The difference between these memory adresses is that" << std::endl <<  "the stack variables are closer together to each other, while the heap ones are not as close." << std::endl << "Furthermore, the heap and stack addresses are far away from each other.";


	delete HeapInt1;
	delete HeapInt2;
	delete HeapInt3;

	HeapInt1 = nullptr;
	HeapInt2 = nullptr;
	HeapInt3 = nullptr;
}