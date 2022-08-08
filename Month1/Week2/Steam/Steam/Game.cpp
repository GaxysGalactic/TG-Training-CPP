#include "Game.h"

FGame::FGame(std::string pName, std::string pStudioName, int pYear, int pMonth, int pDay)
{
	Name = pName;
	StudioName = pStudioName;
	Year = pYear;
	Month = pMonth;
	Day = pDay;
}

std::string FGame::GetName() const
{
	return Name;
}

std::string FGame::GetStudioName() const
{
	return StudioName;
}

std::string FGame::GetReleaseDate() const
{
	return Year + "/" + Month + "/" + Day
}

bool FGame::IsValid() const
{
	if (Year < 1972 || Month <= 0 || Month > 12 || Day <= 0 || Day > 31)
	{
		return false;
	}

	else
	{
		return true;
	}
}
