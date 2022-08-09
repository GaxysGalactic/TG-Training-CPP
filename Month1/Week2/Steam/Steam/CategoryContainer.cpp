#include "CategoryContainer.h"

FCategoryContainer::FCategoryContainer()
{
	CategoryCount = 0;
}

bool FCategoryContainer::AddCategory(FCategory pCategory)
{
	if (CategoryCount < MaxCategoryCount)
	{
		Categories[CategoryCount] = pCategory;
		CategoryCount++;
		return true;
	}
	return false;
}

bool FCategoryContainer::DeleteCategory(int Index)
{
	if (Index < CategoryCount)
	{
		for (; Index < CategoryCount; Index++)
		{
			Categories[Index] = Categories[Index + 1];
		}
		CategoryCount--;
		return true;
	}
	return false;
}
