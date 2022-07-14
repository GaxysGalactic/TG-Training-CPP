#include "Spotify.h"


/*
* EXERCISE 3 (contd)
* Test your program up until here. Create a main.cpp file and implement the main method. In here, create a couple playlists with a couple songs and add them to a PlaylistContainer instance. Then, get those same playlists using the getter from the instance and display the playlists in the console. 

* What happens when you try to get a playlist with an out of bounds index? How would you handle it?

* When you make sure everything is working, you can continue to the next exercise.
*/
void debugApp()
{
	//First Playlist. Bohemian Rhapsody should not be able to be added due to song length.
	Song songOne("All Star", "Smash Mouth", 175);
	Song songTwo("Never Gonna Give You Up", "Rick Astley", 135);
	Song songThree("Country Roads", "John Denver", 192);
	Song songFour("Bohemian Rhapsody", "Queen", 361);

	Playlist playlistOne("Greatest Hits 2022");
	playlistOne.addSong(songOne);
	playlistOne.addSong(songTwo);
	playlistOne.addSong(songThree);
	playlistOne.addSong(songFour);

	//Second Playlist.
	Song songFive("Hic Svnt Leones", "The Primals", 264);
	Song songSix("Metal", "The Primals", 243);
	Song songSeven("Exponential Entropy", "The Primals", 198);
	Song songEight("eScape", "The Primals", 223);

	Playlist playlistTwo("FFXIV Primals Mashup");
	playlistTwo.addSong(songFive);
	playlistTwo.addSong(songSix);
	playlistTwo.addSong(songSeven);
	playlistTwo.addSong(songEight);

	//Third Playlist
	Song songNine("Despacito", "Luis Fonsi", 359);
	Song songTen("Despacito (English Version)", "Justin Bieber", 358);

	Playlist playlistThree("Despacito 24/7");
	playlistThree.addSong(songNine);
	playlistThree.addSong(songTen);


	//PlaylistContainer
	PlaylistContainer playlistBox;
	playlistBox.addPlaylist(playlistOne);
	playlistBox.addPlaylist(playlistTwo);
	playlistBox.addPlaylist(playlistThree);


	//Display Playlists
	std::cout << "Displaying Playlists...." << std::endl << std::endl;

	playlistBox.getPlaylist(0).displayPlaylist();

	std::cout << std::endl << std::endl;

	playlistBox.getPlaylist(1).displayPlaylist();

	std::cout << std::endl << std::endl;

	playlistBox.getPlaylist(2).displayPlaylist();

	//std::cout << std::endl << std::endl;
	//playlistBox.getPlaylist(3).displayPlaylist();
}


int main()
{
	//debugApp();
	Spotify spotify;
	spotify.runApp();
	
}