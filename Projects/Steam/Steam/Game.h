#pragma once
#include <iostream>
#include <string>

class FGame
{

private:

	std::string Name;
	std::string StudioName;

	int Year;
	int Month;
	int Day;

public:

	FGame();

	FGame(const std::string& InName, const std::string& InStudioName, const int InYear, const int InMonth, const int InDay);

	std::string GetName() const;

	std::string GetStudioName() const;

	std::string GetReleaseDate() const;

	bool IsValid() const;
};