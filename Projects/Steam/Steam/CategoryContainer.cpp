#include "CategoryContainer.h"

//-------------------------------------------------------------------------------------------
FCategoryContainer::FCategoryContainer()
{
	CategoryCount = 0;
}

//-------------------------------------------------------------------------------------------
FCategoryContainer::FCategoryContainer(const FCategoryContainer& OtherCategoryContainer)
{
	CategoryCount = 0;
	memcpy_s(Categories, sizeof(Categories), OtherCategoryContainer.Categories, sizeof(OtherCategoryContainer.Categories));
	CategoryCount = OtherCategoryContainer.CategoryCount;
}

//-------------------------------------------------------------------------------------------
FCategoryContainer::~FCategoryContainer()
{
}

//-------------------------------------------------------------------------------------------
int FCategoryContainer::GetCategoryCount() const
{
	return CategoryCount;
}

//-------------------------------------------------------------------------------------------
bool FCategoryContainer::GetCategory(const int Index, FCategory& OutCategory) const
{
	if (Index < 0 || Index > CategoryCount)
	{
		return false;
	}
	OutCategory = Categories[Index];
	return true;
}

//-------------------------------------------------------------------------------------------
bool FCategoryContainer::AddCategory(const FCategory& InCategory)
{
	if (CategoryCount < MaxCategoryCount)
	{
		Categories[CategoryCount] = InCategory;
		CategoryCount++;
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
bool FCategoryContainer::DeleteCategory(const int Index)
{
	if (Index < CategoryCount)
	{
		//Cascade the categories into their new positions. This should end up deleting the indexed one as well.
		int i;
		for (i = 0; i < CategoryCount - 1; i++)
		{
			Categories[i] = Categories[i + 1];
		}
		CategoryCount--;
		return true;
	}
	return false;
}

bool FCategoryContainer::AddGameToCategory(const int Index, const FGame& Game)
{
	return Categories[Index].AddGame(Game);
}
