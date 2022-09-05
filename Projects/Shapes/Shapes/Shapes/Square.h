#pragma once


class FSquare
{
private:

	int Side;

public:

	FSquare();

	FSquare(int InSide);

	int GetArea() override const;

	int GetPerimeter() override const;
};