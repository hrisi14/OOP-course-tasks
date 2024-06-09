#pragma once
#include "Song.h"

constexpr size_t MAX_SONGS = 30;

class Playlist
{
	Song songs[MAX_SONGS];
	size_t songsCount = 0;

public:
	bool addASong(const char* songName, unsigned h, unsigned m, unsigned s, const char* genre, const char* fileName);
	void printSongs() const; //name-time-genre
	int findSong(const char* songName) const;
	void findSongPrint(const char* songName) const;
	void printGetSongsByGenre(unsigned char genre) const;
	void sortPlaylist(bool(*isLess)(const Song& lhs, const Song& rhs));
	
	void sortByName();
	void sortByDuration();
	bool addRythm(const char* songName, unsigned k);
	bool mix(const char* firstSong, const char* secondSong);

	bool saveToBinaryFile(const char* songName, const char* fileName) const;
};

