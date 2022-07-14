#pragma once

#include "PlaylistContainer.h"

class Spotify
{
private:

	PlaylistContainer playlists;

	enum class MenuCommand
	{
		MainMenu,
		CreatePlaylist,
		BrowsePlaylists,
		Exit
	};
	
	MenuCommand activeCommand;

public:

	Spotify();

	void runApp();


private:

	void openMainMenu();

	void openCreatePlaylistMenu();

	void openBrowsePlaylistMenu();
};