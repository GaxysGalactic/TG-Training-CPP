#include "Circle.h"

FCircle::FCircle()
{
    Radius = 0;
}

FCircle::FCircle(int InRadius)
{
    Radius = InRadius;
}

double FCircle::GetArea()
{
    return 3.14159265 * Radius * Radius;
}

double FCircle::GetPerimeter()
{
    return 2 * 3.14159265 * Radius;
}


