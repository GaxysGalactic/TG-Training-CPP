/*
* Exercise 5 - Dynamic Allocation for Array Sizes
* Create a Student class that contains a char array of size 5 for a name and an int for an age. Ask
* the user to enter how many students they want in a class. Then, initialize an array of students in
* the heap of exactly the size they asked for. You can now probably tell how dynamic allocation is
* useful.
* Ask the user for a name and an age for each student and then print them all to the screen. Note
* that you won’t be able to use names longer than 4 characters.
* Remember to free any allocated memory.
* 
* 
* 
* Exercise 6 - Dynamic Allocation for Array Sizes 2
* The previous exercise has an obvious problem: Names longer than 4 characters are truncated.
* That’s a terrible program since names generally have more than 4 characters.
* 
* One thing we could do is to extend the size of the char array - we could make it have a size of
* 32. However, most names do not have a size 32, so in the case of ‘Juan’, we’re unnecessarily
* wasting 27 bytes!
* Dynamic memory can help us here too. Change the char array in the student class to be a char
* pointer.
* In main, when you&#39;re getting the input from the user, create a temporary char array of size 32,
* where you store the input.
* Create the following method in your class:
* void setName(const char* newName);
* Pass in the temporary array into this new method you created. Inside the method, allocate the
* amount of memory you need to store the full name in the heap and have the name variable
* point to it.
* You can now copy the memory directly from your temporary variable to your name variable. Use
* memcpy_s to do this. Your program should behave the same way it did before, but now you’ll
* be able to have names of up to 31 characters.
* Please also print to the console why you think we’re doing memcpy_s instead of just doing a
* loop to copy each character.
* 
* 
* 
* Exercise 7 - Destructors and Dynamic Allocation
* We’ve created an important problem in the previous exercise. We managed to save memory by
* allocating the exact amount of memory we need in the heap, but we’ve also created memory
* leaks.
* Let’s see what’s going on, please make sure to compile your program in Debug mode before
* continuing.
* In your main function, before the rest of your program, allocate a new Student object to the
* heap. Then, using your setName function, pass in whatever name you want. Also set an age
* lower than 10 to the student, so it’s easy to recognize in memory.
* Immediately after the allocation, free the memory using the delete keyword. Then, place a
* breakpoint in the line where you’re deleting the memory and run your program.
* The program will halt execution right before the memory is freed. Use the memory viewer to see
* the memory location of your student object. Once you have that view, press F10 to execute the
* line where you free the memory. You’ll see that the memory where your object lived has
* changed to dd. This is a debug compiler code that means it’s uninitialized heap memory, so you
* can be certain the delete worked properly.
* Now, run your program again. This time, go to the memory location of the name of the student.
* Once you’ve found it, press F10 to delete the object. You’ll see that the memory has not been
* freed.
* Print to the console why deleting the student object does not delete the name’s char array.
* 
* 
* 
* Exercise 8 - Destructors and Dynamic Allocation 2
* Keeping in mind that deleting an object calls its destructor right before freeing the memory, and
* using the knowledge you have about destructors, update the program to fix this memory leak.
* You may not delete the memory allocated for the name of a student from outside the student
* object.
* 
* 
* 
* Exercise 9 - Destructors and Dynamic Allocation 3
* Great, we’ve fixed the memory leak! But memory leaks are sneaky, and there’s another
* scenario we’ve failed to take into consideration. We created a setName method where we’re
* allocating memory for the student’s name, that’s good and all, but what happens if you call that
* method twice to update the name a second time. The original memory is not being released in
* that case.
* How would you fix this?
* At this point, it’s obvious that keeping track of all memory allocations in a program can be a
* hassle. In the future, we’ll discuss techniques that will make life a lot easier for us.
*/



#include <iostream>
#include <string>

class FStudent
{

private:
	char* Name;
	int Age;

public:
	
	//--------------------------------------------------------------
	FStudent()
	{
		Name = nullptr;
		Age = 0;
	}

	//--------------------------------------------------------------
	FStudent(int InAge)
	{
		Name = nullptr;
		Age = InAge;
	}

	//--------------------------------------------------------------
	~FStudent()
	{
		delete Name;
	}

	//--------------------------------------------------------------
	void SetName(const char* NewName)
	{
		if (Name)
		{
			delete Name;
			Name = nullptr;
		}

		int NameLength = 0;
		for (int i = 0; NewName[i] != '\0'; i++)
		{
			NameLength++;
		}

		Name = new char[NameLength+1];
		memcpy_s(Name, sizeof(char) * (NameLength+1), NewName, sizeof(char) * (NameLength+1));
	}

	//--------------------------------------------------------------
	void Print()
	{
		std::cout << "Name: " << Name << std::endl;
		std::cout << "Age: " << Age << std::endl;
	}
};



int main()
{
	//-------- Test ----

	FStudent* StudentTest = new FStudent(8);
	StudentTest -> SetName("Chavito"); 

	delete StudentTest;

	std::cout << "On this first test, the Student gets deleted from memory, but the name remains." << std::endl;
	std::cout << "This is because the class Student tries to call the destructor for all its members to free the memory, but Name is a primitive type." << std::endl;
	std::cout << "Therefore, it does not get deleted automatically." << std::endl;

	//------------------

	std::cout << "How many students do you want? " << std::endl;

	int NumberOfStudents;
	std::cin >> NumberOfStudents;

	FStudent* Students = new FStudent[NumberOfStudents];

	std::cout << "You now have " << NumberOfStudents << " students!" << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cout << "Enter a name for student #" << i + 1 << ": ";
		char Name[32];
		std::cin >> Name;

		std::cout << "Enter the age for student #" << i+1 << ": ";
		int Age;
		std::cin >> Age;

		FStudent Student = FStudent(Age);
		Student.SetName(Name);
		Students[i] = Student;
	}


	std::cout << "Here are your students:" << std::endl;

	for (int i = 0; i < NumberOfStudents; i++)
	{
		std::cout << "Student " << i+1 << std::endl;
		Students[i].Print();
	}


	delete[] Students;
}