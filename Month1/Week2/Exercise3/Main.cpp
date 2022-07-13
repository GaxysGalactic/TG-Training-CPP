#include <iostream>
#include <cmath>
#include <iomanip>


class Circle
{
private:
	
	float radius;

public:

	Circle()
	{
		radius = 0.0f;
	}

	Circle(float pRadius)
	{
		radius = pRadius;
	}

	float getArea() const
	{
		return 3.14159265f * std::pow(radius, 2);
	}

	float getPerimeter() const
	{
		return 2 * 3.14159265f * radius;
	}

};


class Square
{
private:

	float sideLength;

public:

	Square()
	{
		sideLength = 0.0f;
	}

	Square(float pSideLength)
	{
		sideLength = pSideLength;
	}

	float getArea() const
	{
		return std::pow(sideLength, 2);
	}

	float getPerimeter() const
	{
		return 4 * sideLength;
	}
};


int main()
{
	std::cout << "Welcome to Create-A-Shape! Please choose from one of the following shapes to proceed:" << std::endl;
	std::cout << "1 - Circle" << std::endl;
	std::cout << "2 - Square" << std::endl;

	std::cout << "Your choice: ";
	int option;
	std::cin >> option;

	while (!std::cin.good() || (option != 1 && option != 2))
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Invalid option. Please try again." << std::endl;
		std::cout << "Your choice: ";
		std::cin >> option;
	}

	if (option == 1)
	{
		float radius;
		std::cout << "Please enter a radius for your circle: ";
		std::cin >> radius;

		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid option. Please try again." << std::endl;
			std::cout << "Please enter a radius for your circle: ";
			std::cin >> radius;
		}

		Circle c(radius);

		std::cout << "Your shape's area is: " << c.getArea() << std::endl;
		std::cout << "Your shape's perimeter is: " << c.getPerimeter() << std::endl;
	}
	else if (option == 2)
	{
		float side;
		std::cout << "Please enter the side length for your square: ";
		std::cin >> side;

		while (!std::cin.good())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid option. Please try again." << std::endl;
			std::cout << "Please enter the side length for your square: ";
			std::cin >> side;
		}

		Square s(side);

		std::cout << "Your shape's area is: " << s.getArea() << std::endl;
		std::cout << "Your shape's perimeter is: " << s.getPerimeter() << std::endl;
	}

}