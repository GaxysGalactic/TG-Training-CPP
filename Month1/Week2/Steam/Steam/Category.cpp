#include "Category.h"

FCategory::FCategory(std::string pName)
{
    Name = pName;
    GameCount = 0;
}

std::string FCategory::GetName() const
{
    return Name;
}

bool FCategory::AddGame(FGame Game)
{
    if (!IsFull())
    {
        Games[GameCount] = Game;
        GameCount++;
        return true;
    }
    return false;
}

bool FCategory::IsFull() const
{
    return GameCount >= MaxGameCount;
}
