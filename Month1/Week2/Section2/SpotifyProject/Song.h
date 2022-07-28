/*
*	EXERCISE 1
* 
*	Create a Song class in your project. Make sure to declare it in a .h and define it in a .cpp.
*
*	Your Song class should have the following private members:
*	std::string songTitle;
*	std::string artistName;
*	int duration;
*
*	It should have a default constructor, a constructor with parameters to initialize the private members, getters, and setters.
*
*	Additionally, implement the following methods:
*	std::string getFormatedDuration(); // Should return duration in the
*							// mm:ss format
*	bool isValid(); // You decide how a song is considered valid or not
*/

#pragma once

#include <iostream>

class Song
{
private:

	std::string songTitle;
	std::string artistName;

	int duration;

public:

	Song();

	Song(std::string pSongTitle, std::string pArtistName, int pDuration);

	void setSongTitle(std::string pSongTitle);

	void setArtistName(std::string pArtistName);

	void setDuration(int pDuration);

	std::string getSongTitle() const;

	std::string getArtistName() const;

	int getDuration() const;

	std::string getFormattedDuration() const;

	bool isValid() const;

};