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

	bool AddCategory(FCategory pCategory);

	bool DeleteCategory(int Index);
};