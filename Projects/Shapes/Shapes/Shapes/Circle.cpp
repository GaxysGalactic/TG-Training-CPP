#include "Circle.h"
#include <numbers>

FCircle::FCircle()
{
    Radius = 0;
}

FCircle::FCircle(int InRadius)
{
    Radius = InRadius;
}

int FCircle::GetArea()
{
    return std::numbers::pi * Radius * Radius;
}

int FCircle::GetPerimeter()
{
    return 2 * std::numbers::pi * Radius;
}


