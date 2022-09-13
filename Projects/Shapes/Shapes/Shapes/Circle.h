#pragma once
#include "Shape.h"

class FCircle : public FShape
{
private:

	float Radius;

public:

	FCircle();

	FCircle(const float InRadius);

	virtual float GetArea() const override;

	virtual float GetPerimeter() const override;
};