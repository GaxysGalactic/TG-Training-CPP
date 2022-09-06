#pragma once

class FShapeBuilder
{

private:

	enum class EMenuCommand
	{
		MainMenu,
		BuiltIn,
		Static,
		Dynamic,
		Exit
	};

	EMenuCommand ActiveCommand;

public:

	FShapeBuilder();

	~FShapeBuilder();

	void RunApp();

private:

	void MainMenu();

	void AskForShapesBuiltIn();

	class FShape** GetBuiltInArray(const int NumberOfShapes) const;

	void PrintBuiltInArray(FShape** Array, const int NumberOfShapes) const;

	void AskForShapesStatic();

	void AskForShapesDynamic();

	void RequestEnterFromInput() const;

	float GetValidFloatInput() const;

	int GetValidIntInput() const;

	int GetValidIntInput(const int LowerBound, const int UpperBound) const;

	void DeleteHeapArray(FShape** Array, const int NumberOfShapes) const;
};