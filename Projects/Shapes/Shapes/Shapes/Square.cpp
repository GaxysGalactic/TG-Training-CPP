#include "Square.h"

FSquare::FSquare()
{
    Side = 0;
}

FSquare::FSquare(int InSide)
{
    Side = InSide;
}


double FSquare::GetArea()
{
    return Side * Side;
}

double FSquare::GetPerimeter()
{
    return 4 * Side;
}


