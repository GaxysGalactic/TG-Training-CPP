#include "Steam.h"

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

		activeCommand = (MenuCommand)Option;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

	} while (!std::cin.good());
}

//-------------------------------------------------------------------------------------------
void Steam::AddGame()
{
	//TODO
	//ActiveCommand = MainMenu;
	ActiveCommand = MenuCommand::Exit;
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
