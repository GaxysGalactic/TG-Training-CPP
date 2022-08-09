#pragma once

#include "CategoryContainer.h"

class Steam
{
private:
	
	FCategoryContainer Categories;
	FCategory Uncategorized;

	enum class MenuCommand
	{
		MainMenu,
		AddGame,
		ManageCategories,
		BrowseGames,
		Exit
	};

	MenuCommand ActiveCommand;

public:

	Steam();

	void RunApp();

private:

	void MainMenu();

	void AddGame();

	int ChooseCategory();

	FGame CreateGame();

	void ManageCategories();

	void CreateCategory();

	void DeleteCategory();

	void BrowseGames();

	int ValidateInt(int Input);

	int ValidateInt(int Input, int LowerBound, int UpperBound);

};