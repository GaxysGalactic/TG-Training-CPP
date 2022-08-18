#include "Steam.h"
#include <string>

//-------------------------------------------------------------------------------------------
//								CONSTRUCTORS & DESTRUCTORS
//-------------------------------------------------------------------------------------------
FSteam::FSteam()
{
	Uncategorized = FCategory("Uncategorized");
	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
FSteam::FSteam(const FSteam& OldSteam)
{
	ActiveCommand = EMenuCommand::MainMenu;
	Categories = OldSteam.Categories;
	Uncategorized = OldSteam.Uncategorized;
	ActiveCommand = OldSteam.ActiveCommand;
}

//-------------------------------------------------------------------------------------------
FSteam::~FSteam()
{

}

//-------------------------------------------------------------------------------------------
//										RUNNING APP
//-------------------------------------------------------------------------------------------
void FSteam::RunApp()
{
	std::cout << "Welcome to Steam!" << std::endl;
	while (ActiveCommand != EMenuCommand::Exit)
	{
		switch (ActiveCommand)
		{
			case EMenuCommand::MainMenu:
				MainMenu();
				break;

			case EMenuCommand::AddGame:
				AddGame();
				break;

			case EMenuCommand::ManageCategories:
				ManageCategories();
				break;

			case EMenuCommand::BrowseGames:
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
void FSteam::MainMenu()
{
	system("CLS");

	std::cout << "Welcome to Steam! What would you like to do?" << std::endl;
	std::cout << "1 - Add Game" << std::endl;
	std::cout << "2 - Manage Categories" << std::endl;
	std::cout << "3 - Browse Games" << std::endl;
	std::cout << "4 - Exit" << std::endl;

	int Option;
	std::cin >> Option;

	ValidateInt(Option, 1, 4);

	ActiveCommand = (EMenuCommand)Option;

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}

//-------------------------------------------------------------------------------------------
//										ADDING A GAME
//-------------------------------------------------------------------------------------------
void FSteam::AddGame()
{
	const int CategoryChosen = ChooseCategory();

	FGame NewGame = CreateGame();

	if (CategoryChosen == -1)
	{
		Uncategorized.AddGame(NewGame);
	}
	else
	{
		Categories.AddGameToCategory(CategoryChosen, NewGame);
	}

	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
int FSteam::ChooseCategory() const
{
	system("CLS");

	
	const int CategoryCount = Categories.GetCategoryCount();
	if (CategoryCount == 0)
	{
		return -1;
	}

	std::cout << "There's categories available for you to add games to. Would you like to add it to a category?" << std::endl;
	std::cout << "0 - No" << std::endl;
	std::cout << "1 - Yes" << std::endl;
	int AddToCategory;
	std::cin >> AddToCategory;

	ValidateInt(AddToCategory, 0, 1);

	int CategoryChosen = -1;
	if (AddToCategory == 1)
	{
			
		ListCategories();

		std::cout << "Please type the number of the category you would like to add to." << std::endl;
		std::cin >> CategoryChosen;

		ValidateInt(CategoryChosen, 0, CategoryCount);
	}
	std::cin.clear();
	RequestEnter();
	return CategoryChosen;
}

//-------------------------------------------------------------------------------------------
FGame FSteam::CreateGame()
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

	ValidateInt(GameYear, 1900, 2022);

	std::cout << "Release Date (Month): ";
	int GameMonth;
	std::cin >> GameMonth;

	ValidateInt(GameMonth, 1, 12);

	std::cout << "Release Date (Day): ";
	int GameDay;
	std::cin >> GameDay;

	ValidateInt(GameDay, 1, 31);

	return FGame(GameName, GameStudioName, GameYear, GameMonth, GameDay);
}

//-------------------------------------------------------------------------------------------
//									MANAGING CATEGORIES
//-------------------------------------------------------------------------------------------
void FSteam::ManageCategories()
{
	system("CLS");

	std::cout << "Welcome to Category Management! What would you like to do?" << std::endl;
	std::cout << "1 - Create a Category" << std::endl;
	std::cout << "2 - Delete a Category" << std::endl;
	int Option;
	std::cin >> Option;

	ValidateInt(Option, 1, 2);

	if (Option == 1)
	{
		CreateCategory();
	}
	else
	{
		DeleteCategory();
	}

	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
void FSteam::CreateCategory()
{
	system("CLS");
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	std::cout << "Please write the name of the category you would like to create: ";
	std::string CategoryName;
	if (std::cin.peek() == '\n')
	{
		return;
	}
	std::cin >> CategoryName;

	FCategory NewCategory(CategoryName);

	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');

	if (Categories.AddCategory(NewCategory))
	{
		std::cout << "Success! You have created the category " << CategoryName << "!" << std::endl;
	}
	else
	{
		std::cout << "Unfortunately, there was an error creating your category. The category list is full." << std::endl;
	}
	RequestEnter();
}

//-------------------------------------------------------------------------------------------
void FSteam::DeleteCategory()
{
	system("CLS");

	const int CategoryCount = Categories.GetCategoryCount();
	if (CategoryCount != 0)
	{
		ListCategories();
		std::cout << "Which category would you like to delete?" << std::endl;
		int CategoryChosen;
		std::cin >> CategoryChosen;

		ValidateInt(CategoryChosen, 0, CategoryCount);

		if (Categories.DeleteCategory(CategoryChosen))
		{
			std::cout << "Success! That category has been deleted." << std::endl;
		}
		else
		{
			std::cout << "There was an error deleting your category." << std::endl;
		}
	}
	else
	{
		std::cout << "Unfortunately, there are no categories available for you to delete." << std::endl;
	}
	std::cin.ignore();
	std::cin.ignore();
}

//-------------------------------------------------------------------------------------------
//									BROWSING GAMES
//-------------------------------------------------------------------------------------------
void FSteam::BrowseGames()
{
	system("CLS");
	for (int i = 0; i < Categories.GetCategoryCount(); i++)
	{
		FCategory CurrentCategory;
		Categories.GetCategory(i, CurrentCategory);
		DisplayCategory(CurrentCategory);
	}
	DisplayCategory(Uncategorized);
	RequestEnter();
	ActiveCommand = EMenuCommand::MainMenu;
}

//-------------------------------------------------------------------------------------------
//									UTILITY FUNCTIONS
//-------------------------------------------------------------------------------------------
void FSteam::RequestEnter() const
{
	std::cin.ignore(INT_MAX, '\n');
}

//-------------------------------------------------------------------------------------------
void FSteam::ValidateInt(int& OutInteger) const
{
	while (std::cin.fail())
	{
		std::cin.clear();
		RequestEnter();
		std::cout << "That is not a valid integer. Please try again." << std::endl;
		std::cin >> OutInteger;
	}
}

//-------------------------------------------------------------------------------------------
void FSteam::ValidateInt(int& OutInteger, const int LowerBound, const int UpperBound) const
{
	while (std::cin.fail() || OutInteger < LowerBound || OutInteger > UpperBound)
	{
		std::cin.clear();
		RequestEnter();
		std::cout << "That is not a valid integer or within the intended range. Please try again." << std::endl;
		std::cin >> OutInteger;
	}
}

//-------------------------------------------------------------------------------------------
void FSteam::ListCategories() const
{
	std::cout << "Here's a list of the available categories:" << std::endl;
	for (int i = 0; i < Categories.GetCategoryCount(); i++)
	{
		FCategory CurrentCategory;
		Categories.GetCategory(i, CurrentCategory);
		std::cout << i << " - " << CurrentCategory.GetName() << std::endl;
	}
}

//-------------------------------------------------------------------------------------------
void FSteam::DisplayCategory(const FCategory& Category) const
{
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "                      " << Category.GetName() << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;


	std::cout << "NAME\t\tSTUDIO\t\tRELEASE DATE" << std::endl;

	if (Category.GetGameCount() == 0)
	{
		std::cout << "There are no games for this category.. :c" << std::endl;
	}
	else
	{
		for (int i = 0; i < Category.GetGameCount(); i++)
		{
			FGame CurrentGame;
			Category.GetGame(i, CurrentGame);
			std::cout << CurrentGame.GetName() << "\t" << CurrentGame.GetStudioName() << "\t" << CurrentGame.GetReleaseDate() << std::endl;
		}
	}
}
