#pragma once
#include "Shape.h"

class FSquare: public FShape
{
private:

	float Side;

public:

	FSquare();

	FSquare(const float InSide);

	virtual float GetArea() const override;

	virtual float GetPerimeter() const override;
};