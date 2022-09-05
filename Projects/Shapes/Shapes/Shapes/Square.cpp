#include "Square.h"

FSquare::FSquare()
{
    Side = 0;
}

FSquare::FSquare(int InSide)
{
    Side = InSide;
}


int FSquare::GetArea()
{
    return Side * Side;
}

int FSquare::GetPerimeter()
{
    return 4 * Side;
}


