#include "Category.h"

//-------------------------------------------------------------------------------------------
FCategory::FCategory()
{
    GameCount = 0;
}

//-------------------------------------------------------------------------------------------
FCategory::FCategory(const FCategory& OldCategory)
{
    GameCount = 0;
    Name = OldCategory.Name;
    memcpy_s(Games, sizeof(Games), OldCategory.Games, sizeof(OldCategory.Games));
    GameCount = OldCategory.GameCount;
}

//-------------------------------------------------------------------------------------------
FCategory::FCategory(const std::string& InName)
{
    Name = InName;
    GameCount = 0;
}

FCategory::~FCategory()
{

}

//-------------------------------------------------------------------------------------------
const std::string& FCategory::GetName() const
{
    return Name;
}

//-------------------------------------------------------------------------------------------
bool FCategory::GetGame(const int Index, FGame& OutGame) const
{
    if (Index < 0 || Index > GameCount)
    {
        return false;
    }
    OutGame = Games[Index];
    return true;
}

//-------------------------------------------------------------------------------------------
int FCategory::GetGameCount() const
{
    return GameCount;
}

//-------------------------------------------------------------------------------------------
bool FCategory::AddGame(const FGame& Game)
{
    if (!IsFull())
    {
        Games[GameCount] = Game;
        GameCount++;
        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------
bool FCategory::IsFull() const
{
    return GameCount >= MaxGameCount;
}
