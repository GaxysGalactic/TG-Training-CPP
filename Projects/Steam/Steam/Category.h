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

	FCategory(const std::string InName);

	std::string GetName() const;

	FGame GetGame(const int Index) const;

	int GetGameCount() const;

	bool AddGame(const FGame Game);

	bool IsFull() const;
};