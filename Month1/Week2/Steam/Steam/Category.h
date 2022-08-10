#pragma once

#include "Game.h"

class FCategory
{
private:

	std::string Name;
	const static int MaxGameCount = 10;
	FGame Games[MaxGameCount];
	int GameCount;

public:

	FCategory();

	FCategory(std::string pName);

	std::string GetName() const;

	FGame GetGame(int Index) const;

	int GetGameCount() const;

	bool AddGame(FGame Game);

	bool IsFull() const;
};