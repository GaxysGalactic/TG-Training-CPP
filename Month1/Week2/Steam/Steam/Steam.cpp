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
