#include "ShapeBuilder.h"
#include "Square.h"
#include "Circle.h"
#include "StaticArray.h"
#include "DynamicArray.h"
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
	FShape** Shapes = FillBuiltInArray(NumberOfShapes);

	//Print Array
	PrintArray(Shapes, NumberOfShapes);
	RequestEnterFromInput();

	//Delete
	DeleteArray(Shapes, NumberOfShapes);
	
	ActiveCommand = EMenuCommand::MainMenu;
	
}

//-------------------------------------------------------------------------------------------
FShape** FShapeBuilder::FillBuiltInArray(const int NumberOfShapes) const
{
	FShape** Shapes = new FShape * [NumberOfShapes];

	for (int i = 0; i < NumberOfShapes; i++)
	{
		system("CLS");
		Shapes[i] = CreateShape();
	}

	return Shapes;
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::PrintArray(FShape** Array, const int NumberOfShapes) const
{
	system("CLS");

	for (int i = 0; i < NumberOfShapes; i++)
	{
		std::cout << "Shape " << i + 1 << std::endl;
		std::cout << "Area: " << Array[i]->GetArea() << std::endl;
		std::cout << "Perimeter: " << Array[i]->GetPerimeter() << std::endl;
	}
	RequestEnterFromInput();
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::DeleteArray(FShape** Array, const int NumberOfShapes) const
{
	for (int i = 0; i < NumberOfShapes; i++)
	{
		delete Array[i];
		Array[i] = nullptr;
	}
	delete[] Array;
	Array = nullptr;
}


//-------------------------------------------------------------------------------------------
//										 STATIC
//-------------------------------------------------------------------------------------------
void FShapeBuilder::AskForShapesStatic()
{
	system("CLS");
	std::cout << "You will now be asked to provide information for 5 Shapes." << std::endl;

	//Fill Array
	TStaticArray<FShape*, 5> Shapes; 
	FillStaticArray(Shapes);

	//Print Array
	PrintArray(Shapes);
	RequestEnterFromInput();

	//Delete Array
	DeleteArray(Shapes);

	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::FillStaticArray(TStaticArray<FShape*, 5>& OutArray) const
{
	RequestEnterFromInput();

	for (int i = 0; i < 5; i++)
	{
		system("CLS");
		OutArray[i] = CreateShape();
	}
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::PrintArray(const TStaticArray<FShape*, 5>& Array) const
{
	system("CLS");

	for (int i = 0; i < Array.GetSize(); i++)
	{
		std::cout << "Shape " << i+1 << std::endl;
		std::cout << "Area: " << Array[i]->GetArea() << std::endl;
		std::cout << "Perimeter: " << Array[i]->GetPerimeter() << std::endl;
	}
	RequestEnterFromInput();
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::DeleteArray(TStaticArray<FShape*, 5>& Array) const
{
	for (int i = 0; i < Array.GetSize(); i++)
	{
		delete Array[i];
		Array[i] = nullptr;
	}
}



//-------------------------------------------------------------------------------------------
//										 DYNAMIC
//-------------------------------------------------------------------------------------------
void FShapeBuilder::AskForShapesDynamic()
{
	system("CLS");
	std::cout << "We're gonna add your shapes to a dynamic array!" << std::endl;
	RequestEnterFromInput();

	//Fill Array
	TDynamicArray<FShape*> Shapes;
	FillDynamicArray(Shapes);

	//Print Array
	PrintArray(Shapes);
	RequestEnterFromInput();

	//Delete
	DeleteArray(Shapes);

	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::FillDynamicArray(TDynamicArray<FShape*>& OutArray) const
{
	bool Continue;
	do
	{
		system("CLS");

		FShape* Shape = CreateShape();
		OutArray.PushBack(Shape);

		std::cout << "Would you like to continue adding more shapes?" << std::endl;
		std::cout << "1 - Yes!!" << std::endl;
		std::cout << "2 - No, please print them." << std::endl;
		
		Continue = GetValidBoolInput(1, 2);
	} while (Continue);
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::PrintArray(const TDynamicArray<FShape*>& Array) const
{
	system("CLS");

	for (int i = 0; i < Array.GetSize(); i++)
	{
		std::cout << "Shape " << i + 1 << std::endl;
		std::cout << "Area: " << Array[i]->GetArea() << std::endl;
		std::cout << "Perimeter: " << Array[i]->GetPerimeter() << std::endl;
	}
	RequestEnterFromInput();
}

//-------------------------------------------------------------------------------------------
void FShapeBuilder::DeleteArray(TDynamicArray<FShape*>& Array) const
{
	for (int i = 0; i < Array.GetSize(); i++)
	{
		delete Array[i];
		Array[i] = nullptr;
	}
}


//-------------------------------------------------------------------------------------------
//									UTILITY FUNCTIONS
//-------------------------------------------------------------------------------------------
FShape* FShapeBuilder::CreateShape() const
{
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

		return Circle;
	}
	else
	{
		system("CLS");
		std::cout << "You chose a square!" << std::endl;
		std::cout << "Type in its side length." << std::endl;
		float Side = GetValidFloatInput();

		FSquare* Square = new FSquare(Side);

		return Square;
	}
}

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
bool FShapeBuilder::GetValidBoolInput(const int ValueTrue, const int ValueFalse) const
{
	int Option;
	std::cin >> Option;
	while (std::cin.fail() || (Option != ValueTrue && Option != ValueFalse))
	{
		std::cin.clear();
		RequestEnterFromInput();
		std::cout << "That is not a valid integer or within the intended range. Please try again." << std::endl;
		std::cin >> Option;
	}
	return Option == ValueTrue;
}

