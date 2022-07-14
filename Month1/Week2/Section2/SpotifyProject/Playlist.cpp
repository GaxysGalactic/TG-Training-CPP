/*
* Instructions found in Playlist.h
*/

#include "Playlist.h"

Playlist::Playlist()
{
	playlistTitle = "N/A";
	songCount = 0;
}

Playlist::Playlist(std::string pPlaylistTitle)
{
	playlistTitle = pPlaylistTitle;
	songCount = 0;
}

void Playlist::setPlaylistTitle(std::string pPlaylistTitle)
{
	playlistTitle = pPlaylistTitle;
}

const std::string Playlist::getPlaylistTitle()
{
	return playlistTitle;
}

bool Playlist::addSong(Song song)
{
	if (song.isValid())
	{
		songs[songCount] = song;
		songCount++;
		return true;
	}
	return false;
}

//Precondition: songIndex is within range (checked by main)
const Song Playlist::getSong(int songIndex)
{
	return songs[songIndex];
}

//Ask if possible to print to console, since Playlist != interface
const void Playlist::displayPlaylist()
{
	std::cout << "Song Title\t\tArtist Name\t\tDuration" << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
		
	for (int i = 0; i < songCount; i++)
	{
		Song currentSong = songs[i];
		std::cout << currentSong.getSongTitle() << "\t\t" << currentSong.getArtistName() << "\t\t" << currentSong.getDuration() << std::endl;
	}
}