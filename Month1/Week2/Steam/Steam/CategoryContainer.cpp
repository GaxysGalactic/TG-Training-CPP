#include "CategoryContainer.h"

//-------------------------------------------------------------------------------------------
FCategoryContainer::FCategoryContainer()
{
	CategoryCount = 0;
}

//-------------------------------------------------------------------------------------------
int FCategoryContainer::GetCategoryCount()
{
	return CategoryCount;
}

//-------------------------------------------------------------------------------------------
FCategory FCategoryContainer::GetCategory(int index)
{
	return Categories[index];
}

//-------------------------------------------------------------------------------------------
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

//-------------------------------------------------------------------------------------------
bool FCategoryContainer::DeleteCategory(int Index)
{
	if (Index < CategoryCount)
	{
		//Cascade the categories into their new positions. This should end up deleting the indexed one as well.
		for (; Index < CategoryCount; Index++)
		{
			Categories[Index] = Categories[Index + 1];
		}
		CategoryCount--;
		return true;
	}
	return false;
}
