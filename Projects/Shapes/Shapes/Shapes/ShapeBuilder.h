#pragma once
#include "StaticArray.h"
#include "DynamicArray.h"

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

	//----------------Built In-------------------------------------------

	void AskForShapesBuiltIn();

	class FShape** FillBuiltInArray(const int NumberOfShapes) const;

	void PrintArray(FShape** Array, const int NumberOfShapes) const;

	void DeleteArray(FShape** Array, const int NumberOfShapes) const;

	//----------------Static---------------------------------------------

	void AskForShapesStatic();

	void FillStaticArray(TStaticArray<FShape*, 5>& OutArray) const;

	void PrintArray(const TStaticArray<FShape*, 5>& Array) const;

	void DeleteArray(TStaticArray<FShape*, 5>& Array) const;

	//----------------Dynamic-------------------------------------------

	void AskForShapesDynamic();

	void FillDynamicArray(TDynamicArray<FShape*>& OutArray) const;

	void PrintArray(const TDynamicArray<FShape*>& Array) const;

	void DeleteArray(TDynamicArray<FShape*>& Array) const;

	//----------------Utilities-------------------------------------------

	FShape* CreateShape() const;

	void RequestEnterFromInput() const;

	float GetValidFloatInput() const;

	int GetValidIntInput() const;

	int GetValidIntInput(const int LowerBound, const int UpperBound) const;

	bool GetValidBoolInput(const int ValueTrue, const int ValueFalse) const;

};