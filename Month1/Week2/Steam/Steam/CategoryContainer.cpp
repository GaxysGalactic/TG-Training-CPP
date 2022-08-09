#include "CategoryContainer.h"

FCategoryContainer::FCategoryContainer()
{
	CategoryCount = 0;
}

void FCategoryContainer::AddCategory(FCategory pCategory)
{
	if (CategoryCount < MaxSongCount)
	{
		Categories[CategoryCount] = pCategory;
		CategoryCount++;
		return true;
	}
	return false;
}

void FCategoryContainer::DeleteCategory(int Index)
{
	if (Index < CategoryCount)
	{
		for (; Index < CategoryCount; Index++)
		{
			Categories[Index] = Categories[Index + 1];
		}
		return true;
	}
	return false;
}
