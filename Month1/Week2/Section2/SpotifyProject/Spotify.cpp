/*
* EXERCISE 4.0
* Finally, let’s use everything we’ve done to make an app. Create a class called Spotify. We’ll need to create 3 different menus for this app: a Main Menu, a Create Playlist Menu, and a Browse Playlist Menu. We also need our app to have a list of playlists, so let’s do that.

* The class should have the following private members.
* PlaylistContainer playlists;

* enum class MenuCommand { MainMenu, CreatePlaylist, BrowsePlaylists, Exit };
* MenuCommand activeCommand;

* Remember to also add a default constructor to the class.

* The menu commands will allow us to navigate between menus with ease, changing menus when the activeCommand changes.

* To do this, we need to define the following public  method
* void runApp();

* runApp should run a loop that will exit if the activeMenuCommand is set to Exit. If it’s not, it should do a switch on the activeMenuCommand to determine what it should do next. The implementations of each switch case can be empty for now, we just need somewhere to include the logic later.
*/


#include "Spotify.h"
#include <string>

Spotify::Spotify()
{
	activeCommand = MenuCommand::MainMenu;
}

void Spotify::runApp()
{
	while (activeCommand != MenuCommand::Exit)
	{
		switch (activeCommand)
		{
			case MenuCommand::MainMenu:
				openMainMenu();
				break;

			case MenuCommand::BrowsePlaylists:
				openBrowsePlaylistMenu();
				break;

			case MenuCommand::CreatePlaylist:
				openCreatePlaylistMenu();
				break;
		}
	}
}


/*
*	EXERCISE 4.1
*	Let’s create a main menu. In your Spotify class, create a new private method:
*	void openMainMenu();
*
*	The openMainMenu method should be called in the runApp method when the activeMenuCommand is MainMenu. With that in mind, it would make sense to initialize the activeMenuCommand to MainMenu. 
*
*	This method should present the user with a list of possible actions. These actions should then be set into the activeMenuCommand variable.
*
*	Example output
*	Welcome to Spotify! What would you like to do?
*	1 - Create a Playlist
*	2 - Browse Playlists
*	3 - Exit
*
*	Make sure to validate input. However, it’s not very pretty to have the console full of repeating text, so you can always refresh the console using the function system(“cls”).
*/


void Spotify::openMainMenu()
{
	do 
	{
		system("CLS");
		std::cout << "Welcome to Spotify! What would you like to do?" << std::endl;
		std::cout << "1 - Create a Playlist" << std::endl;
		std::cout << "2 - Browse Playlists" << std::endl;
		std::cout << "3 - Exit" << std::endl;

		int choice;
		std::cin >> choice;
		activeCommand = (MenuCommand) choice;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (!std::cin.good());
}


/*
*	EXERCISE 4.2
*	With the main menu done, it’s time to create the create-a-playlist menu. You should have the following private methods:
*	void openCreatePlaylistMenu();
*
*	The method should allow the user to enter a name to the playlist and add songs to it.
*
*	Example output
*	Please enter a name for the playlist: Whatever
*
*	Let’s add a song to Whatever!
*	Please enter the song title: Song Title
*	Please enter the artist name: Artist Name
*	Please enter the duration of the song: 155
*
*	Song added!
*
*	1 - Enter another song
*	2 - Go back to main menu
*
*/

void Spotify::openCreatePlaylistMenu()
{
	std::string playlistName;
	std::cout << "Please enter a name for your playlist: ";
	std::getline(std::cin, playlistName);

	Playlist newPlaylist(playlistName);

	int moreSongs;
	do
	{
		system("CLS");
		std::cout << "Let's add a song to " << playlistName << "!" << std::endl;

		std::cout << "Please enter the song title: ";
		std::string songName;
		std::getline(std::cin, songName);

		std::cout << "Please enter the artist name: ";
		std::string songArtist;
		std::getline(std::cin, songArtist);

		std::cout << "Please enter the duration of the song (in seconds): ";
		int songDuration;
		std::cin >> songDuration;

		Song newSong(songName, songArtist, songDuration);
		newPlaylist.addSong(newSong);

		std::cout << "1 - Enter another song" << std::endl;
		std::cout << "2 - Go back to main menu" << std::endl;
		std::cin >> moreSongs;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	} while (moreSongs == 1);

	playlists.addPlaylist(newPlaylist);
	activeCommand = MenuCommand::MainMenu;
}

/*
*	EXERCISE 4.3
*	Let’s create the final menu for our app, the one where you can browse playlists. Create the private method:
*	void openBrowsePlaylistsMenu();
*
*	The method should allow the user to browse the currently created playlist and choose one to be displayed. Choose how you want to make the user choose their next action. The example shows using enter as the key to go back 
*
*	Example output
*	Here are your playlists!
*	1 - Playlist #1
*	2 - Playlist #2
*	3 - Playlist #3
*
*	Which playlist do you want to see: 3
*
*	Example output - continued
*	Here’s Playlist #3!
*
*
*	Title			Artist			Duration
*	Song #1		Artist #1		1:59
*	Song #2		Artist #2		3:27
*
*	1 - Pick another playlist
*	2 - Go back to main menu
*
*	What do you want to do: 
*
*/

void Spotify::openBrowsePlaylistMenu()
{
	std::cout << "Here are your playlists!" << std::endl;

	for (int i = 0; i < playlists.getPlaylistCount(); i++)
	{
		std::cout << i << "- " << playlists.getPlaylist(i).getPlaylistTitle() << std::endl;
	}

	std::cin.clear();

	int choice;
	do
	{
		std::cout << "Which playlist do you want to see? ";
		if (std::cin.peek() == '\n') break;
		int index;
		std::cin >> index;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		if (playlists.getPlaylistCount() <= index)
		{
			std::cout << "You didn't choose a playlist! Please try again." << std::endl;
		}
		else
		{
			system("CLS");
			playlists.getPlaylist(index).displayPlaylist();
		}

		std::cout << "1 - Pick another playlist" << std::endl;
		std::cout << "2 - Go back to main menu" << std::endl;
		std::cin >> choice;

		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');

		system("CLS");
	} while (choice == 1);

	activeCommand = MenuCommand::MainMenu;
}
