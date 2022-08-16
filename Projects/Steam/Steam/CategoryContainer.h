#pragma once

#include "Category.h"

class FCategoryContainer
{
private:

	const static int MaxCategoryCount = 5;
	FCategory Categories[MaxCategoryCount];
	int CategoryCount;

public:

	FCategoryContainer();

	int GetCategoryCount() const;

	FCategory GetCategory(const int Index) const;

	bool AddCategory(const FCategory InCategory);

	bool DeleteCategory(const int Index);

	bool AddGameToCategory(const int Index, const FGame Game);
};