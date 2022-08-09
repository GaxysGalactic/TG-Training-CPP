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
		CreateCategory,
		BrowseGames,
		Exit
	};

	MenuCommand ActiveCommand;

public:

	Steam();

	void RunApp();

	void AddGame();

	void CreateCategory();

	void BrowseGames();

};