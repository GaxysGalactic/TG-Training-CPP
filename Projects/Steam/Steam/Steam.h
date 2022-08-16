#pragma once

#include "CategoryContainer.h"

class FSteam
{
private:
	
	FCategoryContainer Categories;
	FCategory Uncategorized;

	enum class EMenuCommand
	{
		MainMenu,
		AddGame,
		ManageCategories,
		BrowseGames,
		Exit
	};

	EMenuCommand ActiveCommand;

public:

	FSteam();

	void RunApp();

private:

	void MainMenu();

	void AddGame();

	int ChooseCategory() const;

	void CreateGame(FGame& OutGame);

	void ManageCategories();

	void CreateCategory();

	void DeleteCategory();

	void BrowseGames();

	void RequestEnter() const;

	void ValidateInt(int& OutInteger) const;

	void ValidateInt(int& OutInteger, const int LowerBound, const int UpperBound) const;

	void ListCategories() const;

	void DisplayCategory(const FCategory& Category) const;

};