#pragma once
#include "Shape.h"

class FSquare: public FShape
{
private:

	int Side;

public:

	FSquare();

	FSquare(int InSide);

	double GetArea();

	double GetPerimeter();
};