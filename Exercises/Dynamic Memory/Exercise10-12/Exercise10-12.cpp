#include "ClassA.h"
#include "ClassB.h"

int main()
{
	ClassA classA;
	ClassB classB;

	std::cout << "The original error was occurring because of the order of declaration and definition. Either ClassA didn't know about ClassB's existence before setting it as a property, or vice versa. This is because Include will past the code of the other into the file, so one got defined before the other.";

	std::cout << "Forward declarations are really useful for C++, allowing us to only include header files where we are actually using them. This allows for easier readability and no surprises that can come about when you include a header file that in return included a lot of other header files and so on and so forth.";

	std::cout << "It makes sense that it only works for pointers, seeing as how it won't automatically access a default constructor once declared. In that case, the knowledge of what the constructor actually does is probably required, while a pointer can be set to null and given an instance afterwards."

	return 0;
}