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

	FCategory(std::string pName);

	std::string GetName() const;

	void AddGame(FGame Game);

	bool IsFull() const;
};