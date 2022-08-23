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

	FCategoryContainer(const FCategoryContainer& OtherCategoryContainer);

	~FCategoryContainer();

	int GetCategoryCount() const;

	bool GetCategory(const int Index, FCategory& OutCategory) const;

	bool AddCategory(const FCategory& InCategory);

	bool DeleteCategory(const int Index);

	bool AddGameToCategory(const int Index, const FGame& Game);
};