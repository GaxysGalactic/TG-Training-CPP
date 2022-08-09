#include "Steam.h"
#include <string>

//-------------------------------------------------------------------------------------------
Steam::Steam()
{
	Uncategorized = FCategory("Uncategorized");
	ActiveCommand = MenuCommand::MainMenu;
}


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
			//Browse Categories available
			std::cout << "Great! Here's a list of the available categories for you to choose from!" << std::endl;
			for (int i = 0; i < CategoryCount; i++)
			{
				std::cout << i << Categories.GetCategory(i).GetName() << std::endl;
			}
			std::cout << "Please type the number of the category you would like to add to." << std::endl;
			std::cin >> CategoryChosen;

			CategoryChosen = ValidateInt(CategoryChosen, 0, CategoryCount);
		}
	}

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
void Steam::ManageCategories()
{

	ActiveCommand = MenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
void Steam::CreateCategory()
{
	//TODO
	//ActiveCommand = MainMenu;
	ActiveCommand = MenuCommand::Exit;
}

//-------------------------------------------------------------------------------------------
void Steam::DeleteCategory()
{

}

//-------------------------------------------------------------------------------------------
void Steam::BrowseGames()
{
	//TODO
	//ActiveCommand = MainMenu;
	ActiveCommand = MenuCommand::Exit;
}

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
