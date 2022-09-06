#include "ShapeBuilder.h"
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
	std::cout << "BUILT IN" << std::endl;
	std::cin.get();
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
void FShapeBuilder::RequestEnter() const
{
	std::cin.ignore(INT_MAX, '\n');
}

//-------------------------------------------------------------------------------------------
int FShapeBuilder::GetValidIntInput() const
{
	int Option;
	std::cin >> Option;
	while (std::cin.fail())
	{
		std::cin.clear();
		RequestEnter();
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
		RequestEnter();
		std::cout << "That is not a valid integer or within the intended range. Please try again." << std::endl;
		std::cin >> Option;
	}
	return Option;
}
