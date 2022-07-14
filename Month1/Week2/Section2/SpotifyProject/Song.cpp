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

const std::string Song::getSongTitle()
{
	return songTitle;
}

const std::string Song::getArtistName()
{
	return artistName;
}

const int Song::getDuration()
{
	return duration;
}

const std::string Song::getFormattedDuration()
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


const bool Song::isValid()
{
	return duration <= 0;
}
