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

Playlist PlaylistContainer::getPlaylist(int index) const
{
	return playlists[index];
}

int PlaylistContainer::getPlaylistCount() const
{
	return playlistCount;
}
