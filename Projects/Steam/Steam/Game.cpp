#include "Game.h"

//-------------------------------------------------------------------------------------------
FGame::FGame()
{
	Year = 0;
	Month = 0;
	Day = 0;
}

//-------------------------------------------------------------------------------------------
FGame::FGame(const FGame& oldGame)
{
	Name = oldGame.Name;
	StudioName = oldGame.StudioName;
	Year = oldGame.Year;
	Month = oldGame.Month;
	Day = oldGame.Day;
}

//-------------------------------------------------------------------------------------------
FGame::FGame(const std::string& InName, const std::string& InStudioName, const int InYear, const int InMonth, const int InDay)
{
	Name = InName;
	StudioName = InStudioName;
	Year = InYear;
	Month = InMonth;
	Day = InDay;
}

//-------------------------------------------------------------------------------------------
FGame::~FGame()
{
}

//-------------------------------------------------------------------------------------------
const std::string& FGame::GetName() const
{
	return Name;
}

//-------------------------------------------------------------------------------------------
const std::string& FGame::GetStudioName() const
{
	return StudioName;
}

//-------------------------------------------------------------------------------------------
std::string FGame::GetReleaseDate() const
{
	std::string formattedDate;
	formattedDate += std::to_string(Year);
	formattedDate += "/";
	formattedDate += std::to_string(Month);
	formattedDate += "/";
	formattedDate += std::to_string(Day);

	return formattedDate;
}

//-------------------------------------------------------------------------------------------
bool FGame::IsValid() const
{
	return Year >= 1972 && Month > 0 && Month <= 12 && Day > 0 && Day <= 31;
}
