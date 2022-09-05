#pragma once
#include "Shape.h"

class FCircle : public FShape
{
private:

	int Radius;

public:

	FCircle();

	FCircle(int InRadius);

	double GetArea();

	double GetPerimeter();
};