/*
* Exercise 10 - Pointers and Forward Declarations
* Create a new project in your solution for this exercise, we’re no longer using the Student
* Project. Create a header file for a class called ClassA and another header file for a class called
* ClassB.
* Inside ClassA, have a pointer variable of ClassB. Inside ClassB, have a pointer variable of
* ClassA. You’ll need to #include each other’s header files.
* Inside your main function, create an instance of ClassA and an instance of ClassB. The
* main.cpp file should look like this:
* You’ll see that the program can’t compile. The error message will probably not be too helpful,
* but try to think about why this is happening. Remember how #include works to try and figure this
* one out. Print to the console why this error is happening.
* 
* 
* 
* Exercise 11 - Pointers and Forward Declarations 2
* Take a look at this additional resource to understand what forward declarations are and why
* they are important: Link
* Now, use forward declarations to fix the problem you had in the previous exercise. Then, print a
* couple of reasons why forward declarations are useful in c++
* 
* 
* 
* Exercise 12 - Pointers and Forward Declarations 3
* Let’s try one more thing. Now, instead of having a pointer variable of type ClassA in ClassB and
* a pointer variable of ClassB in ClassA, let’s have them be instances instead of pointers. So, if
* ClassA previously looked like this:
* Try compiling the program again and you’ll see that it won’t compile with your forward
* declaration. Print to the console why you think forward declarations don’t work for types that are
* not referenced with pointers.
* Remember from now on that it’s good practice to always use forward declarations wherever
* you can.
*/

#include "ClassA.h"
#include "ClassB.h"
#include <iostream>

int main()
{
	FClassA ClassA;
	FClassB ClassB;

	std::cout << "The original error was occurring because of the order of declaration and definition." <<  std::endl << "Either ClassA didn't know about ClassB's existence before setting it as a property, or vice versa. " << std::endl << "This is because Include will past the code of the other into the file, so one got defined before the other." << std::endl;

	std::cout << "Forward declarations are really useful for C++, allowing us to only include header files where we are actually using them." << std::endl << " This allows for easier readability and no surprises that can come about when you include a header file that in return included a lot of other header files and so on and so forth." << std::endl;

	std::cout << "It makes sense that it only works for pointers, seeing as how it won't automatically access a default constructor once declared." << std::endl << " In that case, the knowledge of what the constructor actually does is probably required, while a pointer can be set to null and given an instance afterwards." << std::endl;

	return 0;
}