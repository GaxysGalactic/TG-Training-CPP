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

	void AskForShapesStatic();

	void AskForShapesDynamic();

	void RequestEnter() const;

	int GetValidIntInput() const;

	int GetValidIntInput(const int LowerBound, const int UpperBound) const;
};