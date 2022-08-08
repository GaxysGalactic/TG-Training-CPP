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
	}
}

void FCategoryContainer::DeleteCategory(int Index)
{
	for (; Index < CategoryCount; Index++)
	{
		Categories[Index] = Categories[Index + 1];
	}
}
