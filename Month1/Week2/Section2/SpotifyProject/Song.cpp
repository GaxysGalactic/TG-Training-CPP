/*
* Instructions found in song.h
*/


#include "Song.h"

Song::Song() 
{
	songTitle = "N/A";
	artistName = "N/A";
	duration = 0;
}

Song::Song(std::string pSongTitle, std::string pArtistName, int pDuration)
{
	songTitle = pSongTitle;
	artistName = pArtistName;
	duration = pDuration;
}

void Song::setSongTitle(std::string pSongTitle)
{
	songTitle = pSongTitle;
}

void Song::setArtistName(std::string pArtistName)
{
	artistName = pArtistName;
}

void Song::setDuration(int pDuration)
{
	duration = pDuration;
}

std::string Song::getSongTitle() const
{
	return songTitle;
}

std::string Song::getArtistName() const
{
	return artistName;
}

int Song::getDuration() const
{
	return duration;
}

std::string Song::getFormattedDuration() const
{
	int hours = duration / 60;
	int seconds = duration % 60;

	std::string formattedDuration = "";

	if (hours < 10)
	{
		formattedDuration += "0";
	}

	formattedDuration += hours;
	formattedDuration += ":";

	if (seconds < 10)
	{
		formattedDuration += "0";
	}

	formattedDuration += seconds;

	return formattedDuration;
}


bool Song::isValid() const
{
	return duration <= 0;
}
