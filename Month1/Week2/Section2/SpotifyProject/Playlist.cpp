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

std::string Playlist::getPlaylistTitle() const
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
Song Playlist::getSong(int songIndex) const
{
	return songs[songIndex];
}

//Ask if possible to print to console, since Playlist != interface
void Playlist::displayPlaylist() const
{
	std::cout << "Song Title\t\tArtist Name\t\tDuration" << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
		
	for (int i = 0; i < songCount; i++)
	{
		Song currentSong = songs[i];
		std::cout << currentSong.getSongTitle() << "\t\t" << currentSong.getArtistName() << "\t\t" << currentSong.getDuration() << std::endl;
	}
}