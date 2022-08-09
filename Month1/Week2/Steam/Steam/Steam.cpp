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

			case MenuCommand::CreateCategory:
				CreateCategory();
				break;

			case MenuCommand::BrowseGames:
				BrowseGames();
				break;
		}
	}
}


//-------------------------------------------------------------------------------------------
void Steam::MainMenu()
{
	do
	{
		system("CLS");

		std::cout << "Welcome to Steam! What would you like to do?" << std::endl;
		std::cout << "1 - Add Game" << std::endl;
		std::cout << "2 - Create Category" << std::endl;
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

	//Choose a Category

	int CategoryChosen = -1;
	int CategoryCount = Categories.GetCategoryCount();
	if (CategoryCount != 0)
	{
		std::cout << "There's categories available for you to add games to. Would you like to add it to a category?" << std::endl;
		std::cout << "0 - No" << std::endl;
		std::cout << "1 - Yes" << std::endl;
		int AddToCategory;
		std::cin >> AddToCategory;

		//Input Validation
		while (!std::cin.good() || AddToCategory < 0 || AddToCategory > 1)
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "That is not a valid option. Please try again." << std::endl;
			std::cin >> AddToCategory;
		}

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

			//Input Validation
			while (!std::cin.good() || CategoryChosen < 0 || CategoryChosen > CategoryCount)
			{
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				std::cout << "That is not a valid option. Please try again." << std::endl;
				std::cin >> CategoryChosen;
			}
		}
	}

	//"Create" Game
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

	//Input Validation
	while (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "That is not a valid integer. Please try again." << std::endl;
		std::cin >> GameYear;
	}

	std::cout << "Release Date (Month): ";
	int GameMonth;
	std::cin >> GameMonth;

	//Input Validation
	while (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "That is not a valid integer. Please try again." << std::endl;
		std::cin >> GameMonth;
	}

	std::cout << "Release Date (Day): ";
	int GameDay;
	std::cin >> GameDay;

	//Input Validation
	while (!std::cin.good())
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "That is not a valid integer. Please try again." << std::endl;
		std::cin >> GameDay;
	}

	FGame NewGame(GameName, GameStudioName, GameYear, GameMonth, GameDay);

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
void Steam::CreateCategory()
{
	//TODO
	//ActiveCommand = MainMenu;
	ActiveCommand = MenuCommand::Exit;
}

//-------------------------------------------------------------------------------------------
void Steam::BrowseGames()
{
	//TODO
	//ActiveCommand = MainMenu;
	ActiveCommand = MenuCommand::Exit;
}
