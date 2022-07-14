/*
* EXERCISE 3
* 
* Create a new class called PlaylistContainer. PlaylistContainer should be a collection of playlists, so it should look very similar to the Playlist class.
* It should have the following private members:
* const static int MaxPlaylistCount;
* Playlist playlists[MaxPlaylistCount];
* int playlistCount;

* The class should have a default constructor, a method to add a playlist, a method to get a playlist with an index, and a method to know the current playlist count.

*/

#pragma once

#include "Playlist.h"

class PlaylistContainer
{
private:
	const static int MaxPlaylistCount = 10;
	Playlist playlists[MaxPlaylistCount];
	int playlistCount;

public:

	PlaylistContainer();

	void addPlaylist(Playlist pPlaylist);

	Playlist getPlaylist(int index);

	int getPlaylistCount();

};