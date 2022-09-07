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

	void PrintBuiltInArray(FShape** Array, const int NumberOfShapes) const;

	void DeleteBuiltInArray(FShape** Array, const int NumberOfShapes) const;

	//----------------Static---------------------------------------------

	void AskForShapesStatic();

	TStaticArray<FShape*, 5> FillStaticArray() const;

	void PrintStaticArray(TStaticArray<FShape*, 5>& Array) const;

	void DeleteStaticArray(TStaticArray<FShape*, 5>& Array) const;

	//----------------Dynamic-------------------------------------------

	void AskForShapesDynamic();

	TDynamicArray<FShape*> FillDynamicArray() const;

	void PrintDynamicArray(TDynamicArray<FShape*>& Array) const;

	void DeleteDynamicArray(TDynamicArray<FShape*>& Array) const;

	//----------------Utilities-------------------------------------------

	FShape* CreateShape() const;

	void RequestEnterFromInput() const;

	float GetValidFloatInput() const;

	int GetValidIntInput() const;

	int GetValidIntInput(const int LowerBound, const int UpperBound) const;

};