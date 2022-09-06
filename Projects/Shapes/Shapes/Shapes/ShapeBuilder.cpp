#include "ShapeBuilder.h"
#include "Square.h"
#include "Circle.h"
#include <iostream>


//-------------------------------------------------------------------------------------------
//								CONSTRUCTORS & DESTRUCTORS
//-------------------------------------------------------------------------------------------
FShapeBuilder::FShapeBuilder()
{
	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
FShapeBuilder::~FShapeBuilder()
{
}


//-------------------------------------------------------------------------------------------
//										RUNNING APP
//-------------------------------------------------------------------------------------------
void FShapeBuilder::RunApp()
{
	std::cout << "Welcome to ShapeBuilder!" << std::endl;
	while (ActiveCommand != EMenuCommand::Exit)
	{
		switch (ActiveCommand)
		{
		case EMenuCommand::MainMenu:
			MainMenu();
			break;

		case EMenuCommand::BuiltIn:
			AskForShapesBuiltIn();
			break;

		case EMenuCommand::Static:
			AskForShapesStatic();
			break;

		case EMenuCommand::Dynamic:
			AskForShapesDynamic();
			break;

		default:
			ActiveCommand = EMenuCommand::Exit;
			break;
		}
	}
	system("CLS");

	std::cout << "Thanks for using ShapeBuilder! Please come back soon!" << std::endl;
}


//-------------------------------------------------------------------------------------------
//										MAIN MENU
//-------------------------------------------------------------------------------------------
void FShapeBuilder::MainMenu()
{
	system("CLS");

	std::cout << "Welcome to ShapeBuilder! Where would you like to store your shapes?" << std::endl;
	std::cout << "1 - BuiltIn Array" << std::endl;
	std::cout << "2 - Static Array" << std::endl;
	std::cout << "3 - Dynamic Array" << std::endl;
	std::cout << "4 - Exit" << std::endl;

	int Option = GetValidIntInput(1, 4);

	ActiveCommand = (EMenuCommand)Option;

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}


//-------------------------------------------------------------------------------------------
//										BUILT IN
//-------------------------------------------------------------------------------------------
void FShapeBuilder::AskForShapesBuiltIn()
{
	system("CLS");

	std::cout << "We're gonna add your shapes to a built in array!" << std::endl;
	std::cout << "How many shapes would you like to add?" << std::endl;


	//Fill Array
	int NumberOfShapes = GetValidIntInput(0, INT_MAX);

	FShape** Shapes = GetBuiltInArray(NumberOfShapes);

	//Print Array
	PrintBuiltInArray(Shapes, NumberOfShapes);

	RequestEnterFromInput();


	//Delete
	DeleteHeapArray(Shapes, NumberOfShapes);
	
	ActiveCommand = EMenuCommand::MainMenu;
	
}

//-------------------------------------------------------------------------------------------
FShape** FShapeBuilder::GetBuiltInArray(const int NumberOfShapes) const
{
	FShape** Shapes = new FShape * [NumberOfShapes];

	for (int i = 0; i < NumberOfShapes; i++)
	{
		system("CLS");

		std::cout << "Shape " << i + 1 << std::endl;
		std::cout << "Choose your Shape!" << std::endl;
		std::cout << "1 - Circle" << std::endl;
		std::cout << "2 - Square" << std::endl;

		int ShapeChosen = GetValidIntInput(1, 2);

		if (ShapeChosen == 1)
		{
			system("CLS");
			std::cout << "You chose a circle!" << std::endl;
			std::cout << "Type in its radius." << std::endl;
			float Radius = GetValidFloatInput();

			FCircle* Circle = new FCircle(Radius);

			Shapes[i] = Circle;
		}
		else
		{
			system("CLS");
			std::cout << "You chose a square!" << std::endl;
			std::cout << "Type in its side length." << std::endl;
			float Side = GetValidFloatInput();

			FSquare* Square = new FSquare(Side);

			Shapes[i] = Square;
		}
	}

	return Shapes;
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::PrintBuiltInArray(FShape** Array, const int NumberOfShapes) const
{
	for (int i = 0; i < NumberOfShapes; i++)
	{
		std::cout << "Shape " << i << std::endl;
		std::cout << "Area: " << Array[i]->GetArea() << std::endl;
		std::cout << "Perimeter: " << Array[i]->GetPerimeter() << std::endl;
	}
	RequestEnterFromInput();
}


//-------------------------------------------------------------------------------------------
//										 STATIC
//-------------------------------------------------------------------------------------------
void FShapeBuilder::AskForShapesStatic()
{
	std::cout << "STATIC" << std::endl;
	std::cin.get();
}


//-------------------------------------------------------------------------------------------
//										 DYNAMIC
//-------------------------------------------------------------------------------------------
void FShapeBuilder::AskForShapesDynamic()
{
	std::cout << "DYNAMIC" << std::endl;
	std::cin.get();
}


//-------------------------------------------------------------------------------------------
//									UTILITY FUNCTIONS
//-------------------------------------------------------------------------------------------
void FShapeBuilder::RequestEnterFromInput() const
{
	std::cin.ignore(INT_MAX, '\n');
}

//-------------------------------------------------------------------------------------------
float FShapeBuilder::GetValidFloatInput() const
{
	float Option;
	std::cin >> Option;
	while (std::cin.fail())
	{
		std::cin.clear();
		RequestEnterFromInput();
		std::cout << "That is not a valid double. Please try again." << std::endl;
		std::cin >> Option;
	}
	return Option;
}

//-------------------------------------------------------------------------------------------
int FShapeBuilder::GetValidIntInput() const
{
	int Option;
	std::cin >> Option;
	while (std::cin.fail())
	{
		std::cin.clear();
		RequestEnterFromInput();
		std::cout << "That is not a valid integer. Please try again." << std::endl;
		std::cin >> Option;
	}
	return Option;
}

//-------------------------------------------------------------------------------------------
int FShapeBuilder::GetValidIntInput(const int LowerBound, const int UpperBound) const
{
	int Option;
	std::cin >> Option;
	while (std::cin.fail() || Option < LowerBound || Option > UpperBound)
	{
		std::cin.clear();
		RequestEnterFromInput();
		std::cout << "That is not a valid integer or within the intended range. Please try again." << std::endl;
		std::cin >> Option;
	}
	return Option;
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::DeleteHeapArray(FShape** Array, const int NumberOfShapes) const
{
	for (int i = 0; i < NumberOfShapes; i++)
	{
		delete Array[i];
		Array[i] = nullptr;
	}
	delete Array;
	Array = nullptr;
}