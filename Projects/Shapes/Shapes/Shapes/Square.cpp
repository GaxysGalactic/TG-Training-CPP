#include "Square.h"

//-------------------------------------------------------------------------------------------
FSquare::FSquare()
{
    Side = 0;
}

//-------------------------------------------------------------------------------------------
FSquare::FSquare(const float InSide)
{
    Side = InSide;
}

//-------------------------------------------------------------------------------------------
float FSquare::GetArea() const
{
    return Side * Side;
}

//-------------------------------------------------------------------------------------------
float FSquare::GetPerimeter() const
{
    return 4 * Side;
}


