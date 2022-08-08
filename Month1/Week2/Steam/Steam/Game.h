#pragma once
#include <iostream>

class FGame
{
private:

	std::string Name;
	std::string StudioName;
	int Year;
	int Month;
	int Day;

public:

	FGame(std::string pName, std::string pStudioName, int pYear, int pMonth, int pDay);

	std::string GetName() const;

	std::string GetStudioName() const;

	std::string GetReleaseDate() const;

	bool IsValid() const;
};