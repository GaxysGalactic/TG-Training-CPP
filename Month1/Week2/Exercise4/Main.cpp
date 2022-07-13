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