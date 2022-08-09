#include "Steam.h"
#include <string>

//-------------------------------------------------------------------------------------------
//										CONSTRUCTOR
//-------------------------------------------------------------------------------------------
Steam::Steam()
{
	Uncategorized = FCategory("Uncategorized");
	ActiveCommand = MenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
//										RUNNING APP
//-------------------------------------------------------------------------------------------
void Steam::RunApp()
{
	std::cout << "Welcome to Steam!" << std::endl;
	while (ActiveCommand != MenuCommand::Exit)
	{
		switch (ActiveCommand)
		{
			case MenuCommand::MainMenu:
				MainMenu();
				break;

			case MenuCommand::AddGame:
				AddGame();
				break;

			case MenuCommand::ManageCategories:
				ManageCategories();
				break;

			case MenuCommand::BrowseGames:
				BrowseGames();
				break;
		}
	}
	system("CLS");

	std::cout << "Thanks for using Steam! Please come back soon!" << std::endl;
}

//-------------------------------------------------------------------------------------------
//										MAIN MENU
//-------------------------------------------------------------------------------------------
void Steam::MainMenu()
{
	do
	{
		system("CLS");

		std::cout << "Welcome to Steam! What would you like to do?" << std::endl;
		std::cout << "1 - Add Game" << std::endl;
		std::cout << "2 - Manage Categories" << std::endl;
		std::cout << "3 - Browse Games" << std::endl;
		std::cout << "4 - Exit" << std::endl;

		int Option;
		std::cin >> Option;

		while (!std::cin.good() || Option < 1 || Option > 4)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "INVALID INPUT. Please try again." << std::endl;
			std::cin >> Option;
		}

		ActiveCommand = (MenuCommand)Option;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

	} while (!std::cin.good());
}

//-------------------------------------------------------------------------------------------
//										ADDING A GAME
//-------------------------------------------------------------------------------------------
void Steam::AddGame()
{

	int CategoryChosen = ChooseCategory();

	FGame NewGame = CreateGame();

	if (CategoryChosen == -1)
	{
		Uncategorized.AddGame(NewGame);
	}
	else
	{
		Categories.GetCategory(CategoryChosen).AddGame(NewGame);
	}

	ActiveCommand = MenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
int Steam::ChooseCategory()
{
	system("CLS");

	int CategoryChosen = -1;
	int CategoryCount = Categories.GetCategoryCount();
	if (CategoryCount != 0)
	{
		std::cout << "There's categories available for you to add games to. Would you like to add it to a category?" << std::endl;
		std::cout << "0 - No" << std::endl;
		std::cout << "1 - Yes" << std::endl;
		int AddToCategory;
		std::cin >> AddToCategory;

		AddToCategory = ValidateInt(AddToCategory, 0, 1);

		if (AddToCategory == 1)
		{
			
			ListCategories();

			std::cout << "Please type the number of the category you would like to add to." << std::endl;
			std::cin >> CategoryChosen;

			CategoryChosen = ValidateInt(CategoryChosen, 0, CategoryCount);
		}
	}
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	return CategoryChosen;
}

//-------------------------------------------------------------------------------------------
FGame Steam::CreateGame()
{
	system("CLS");

	std::cout << "Please provide the details about the game to the best of your ability." << std::endl;

	std::cout << "Game: ";
	std::string GameName;
	std::getline(std::cin, GameName);

	std::cout << "Developer: ";
	std::string GameStudioName;
	std::getline(std::cin, GameStudioName);

	std::cout << "Release Date (Year): ";
	int GameYear;
	std::cin >> GameYear;

	GameYear = ValidateInt(GameYear, 1900, 2022);

	std::cout << "Release Date (Month): ";
	int GameMonth;
	std::cin >> GameMonth;

	GameMonth = ValidateInt(GameMonth, 1, 12);

	std::cout << "Release Date (Day): ";
	int GameDay;
	std::cin >> GameDay;

	GameDay = ValidateInt(GameDay, 1, 31);

	FGame NewGame(GameName, GameStudioName, GameYear, GameMonth, GameDay);

	return NewGame;
}

//-------------------------------------------------------------------------------------------
//									MANAGING CATEGORIES
//-------------------------------------------------------------------------------------------
void Steam::ManageCategories()
{
	system("CLS");

	std::cout << "Welcome to Category Management! What would you like to do?" << std::endl;
	std::cout << "1 - Create a Category" << std::endl;
	std::cout << "2 - Delete a Category" << std::endl;
	int Option;
	std::cin >> Option;

	Option = ValidateInt(Option, 1, 2);

	if (Option == 1)
	{
		CreateCategory();
	}
	else
	{
		DeleteCategory();
	}

	ActiveCommand = MenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
void Steam::CreateCategory()
{
	system("CLS");
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	std::cout << "Please write the name of the category you would like to create: ";
	std::string CategoryName;
	if (std::cin.peek() == '\n') return;
	std::cin >> CategoryName;

	FCategory NewCategory(CategoryName);

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	if (Categories.AddCategory(NewCategory))
	{
		std::cout << "Success! You have created the category " << CategoryName << "!" << std::endl;
		std::cin.ignore();
	}
	else
	{
		std::cout << "Unfortunately, there was an error creating your category. The category list is full." << std::endl;
		std::cin.ignore();
	}

}

//-------------------------------------------------------------------------------------------
void Steam::DeleteCategory()
{
	system("CLS");

	int CategoryCount = Categories.GetCategoryCount();
	if (CategoryCount != 0)
	{
		ListCategories();
		std::cout << "Which category would you like to delete?" << std::endl;
		int CategoryChosen;
		std::cin >> CategoryChosen;

		CategoryChosen = ValidateInt(CategoryChosen, 0, CategoryCount);

		if (Categories.DeleteCategory(CategoryChosen))
		{
			std::cout << "Success! That category has been deleted." << std::endl;
			std::cin.ignore();
			std::cin.ignore();
		}
		else
		{
			std::cout << "There was an error deleting your category." << std::endl;
			std::cin.ignore();
			std::cin.ignore();
		}
	}
	else
	{
		std::cout << "Unfortunately, there are no categories available for you to delete." << std::endl;
		std::cin.ignore();
		std::cin.ignore();
	}
}

//-------------------------------------------------------------------------------------------
//									BROWSING GAMES
//-------------------------------------------------------------------------------------------
void Steam::BrowseGames()
{
	//TODO
	//ActiveCommand = MenuCommand::MainMenu;
	ActiveCommand = MenuCommand::Exit;
}

//-------------------------------------------------------------------------------------------
//									UTILITY FUNCTIONS
//-------------------------------------------------------------------------------------------
int Steam::ValidateInt(int Input)
{
	while (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "That is not a valid integer. Please try again." << std::endl;
		std::cin >> Input;
	}
	return Input;
}

//-------------------------------------------------------------------------------------------
int Steam::ValidateInt(int Input, int LowerBound, int UpperBound)
{
	while (!std::cin.good() || Input < LowerBound || Input > UpperBound)
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "That is not a valid integer or within the intended range. Please try again." << std::endl;
		std::cin >> Input;
	}
	return Input;
}

//-------------------------------------------------------------------------------------------
void Steam::ListCategories()
{
	std::cout << "Here's a list of the available categories:" << std::endl;
	for (int i = 0; i < Categories.GetCategoryCount(); i++)
	{
		std::cout << i << " - " << Categories.GetCategory(i).GetName() << std::endl;
	}
}
