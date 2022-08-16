#include "Category.h"

//-------------------------------------------------------------------------------------------
FCategory::FCategory()
{
    GameCount = 0;
}

//-------------------------------------------------------------------------------------------
FCategory::FCategory(const std::string InName)
{
    Name = InName;
    GameCount = 0;
}

//-------------------------------------------------------------------------------------------
std::string FCategory::GetName() const
{
    return Name;
}

//-------------------------------------------------------------------------------------------
FGame FCategory::GetGame(const int Index) const
{
    return Games[Index];
}

//-------------------------------------------------------------------------------------------
int FCategory::GetGameCount() const
{
    return GameCount;
}

//-------------------------------------------------------------------------------------------
bool FCategory::AddGame(const FGame Game)
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
