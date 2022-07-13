/*
Exercise 4 - Printer!

Create a printer class. This class should allow you to store a string and then output it in different formats. Ask the user to input a string and then show what your printer can do! Remember to use char arrays instead of strings and avoid the std namespace.

You class should have the following methods:
Printer();
Printer(std::string outputString);
void Print();
void PrintReversed();
void PrintSpaced(int spaces);
void PrintVertically();

Example output
Welcome! Please enter a string: Hello!
Hello!
!olleH
H   e   l   l   o   !
H
e
l
l
o
!


*/


#include <iostream>


class Printer
{
private:

	char OutputString[50];
	int size;

public:

	Printer()
	{
		OutputString[0] = '\0';
		size = 0;
	}

	Printer(std::string outputString)
	{
		size = outputString.length();

		for (int i = 0; i < size; i++)
		{
			OutputString[i] = outputString[i];
		}
		OutputString[size] = '\0';
	}

	void Print()
	{
		std::cout << OutputString << std::endl;
	}

	void PrintReversed()
	{
		char myReversedString[50];

		for (int i = 0; i < size; i++)
		{
			myReversedString[size - i - 1] = OutputString[i];
		}
		myReversedString[size] = '\0';

		std::cout << myReversedString << std::endl;
	}

	void PrintSpaced(int spaces)
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << OutputString[i];

			for (int j = 0; j < spaces; j++)
			{
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	void PrintVertically()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << OutputString[i] << std::endl;
		}
	}
};


int main()
{
	Printer p("Hello");
	p.Print();
	p.PrintReversed();
	p.PrintSpaced(5);
	p.PrintVertically();
}