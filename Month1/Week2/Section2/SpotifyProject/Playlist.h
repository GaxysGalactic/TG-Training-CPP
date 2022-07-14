/*
*	EXERCISE 2
* 
* Create a new class called Playlist. Playlists should be containers for songs, so it should let the user add songs to the playlist.
*
*	It should have the following private members. 
*	const static int MaxSongCount;
*	std::string playlistTitle;
*	Song songs[MaxSongCount];
*	int songCount;
*
*	The class should have a default constructor, a constructor that initializes the playlist title, and a getter and setter for the playlist name.
*
*	Additionally, implement the following methods:
*	bool addSong(Song song);
*	Song getSong(int songIndex);
*	void displayPlaylist();
*
*	Since we’re using a fixed array of songs, addSong should not allow any more songs than the MaxSongCount to be added. It also shouldn’t add invalid songs. In any of these cases where a song can’t be added, you should return false.
*
*	displayPlaylist should display the songs in the following format:
*	Song Title		Artist Name		Duration
*	-----------------------------------------------------------------------
*	Song #1		Artist #1		Duration #1
*	Song #2		Artist #2		Duration #2
*
*/


#pragma once

#include "Song.h"

class Playlist
{
private:

	const static int MaxSongCount = 20;
	std::string playlistTitle;
	Song songs[MaxSongCount];
	int songCount;

public:

	Playlist();

	Playlist(std::string pPlaylistTitle);

	void setPlaylistTitle(std::string pPlaylistTitle);

	std::string getPlaylistTitle();

	bool addSong(Song song);

	Song getSong(int songIndex);

	void displayPlaylist();
};