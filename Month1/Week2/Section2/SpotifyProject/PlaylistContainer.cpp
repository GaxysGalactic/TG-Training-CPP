/*
* Instructions in PlaylistContainer.h
*/

#include "PlaylistContainer.h"

PlaylistContainer::PlaylistContainer()
{
	playlistCount = 0;
}

void PlaylistContainer::addPlaylist(Playlist pPlaylist)
{
	playlists[playlistCount] = pPlaylist;
	playlistCount++;
}

const Playlist PlaylistContainer::getPlaylist(int index)
{
	return playlists[index];
}

const int PlaylistContainer::getPlaylistCount()
{
	return playlistCount;
}
