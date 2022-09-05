#pragma once

class FCircle
{
private:

	int Radius;

public:

	FCircle();

	FCircle(int InRadius);

	int GetArea() override const;

	int GetPerimeter() override const;
};