/*
Exercise 3 - Shapes and Areas

Create two classes: a Circle class and a Square class. For each class, take in the necessary information to calculate its area and perimeter.  Remember to validate input.

Ask the user if they want to create a circle or a square. For their pick, ask the necessary information to create the shape. Then, tell them the area and the perimeter of their shape.

Your class should have the following methods:
ExampleShape();
ExampleShape( Params );
float GetArea();
float GetPerimeter();

Example output
Welcome to create - a - shape, what type of shape do you want ?
1 - Circle
2 - Square
Your choice : 1

Enter radius for your circle : 30
Your shape’s area : 2827.43
Your shape’s perimeter : 188.5


*/


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
		return 3.14159265f * std::pow(radius, 2.0f);
	}

	float getPerimeter() const
	{
		return 2.0f * 3.14159265f * radius;
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
		return std::pow(sideLength, 2.0f);
	}

	float getPerimeter() const
	{
		return 4.0f * sideLength;
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