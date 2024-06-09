#include <iostream>
#pragma once
#include "Song.h"
#include "Playlist.h"

int main()
{
	std::ofstream ofs1("song2", std::ios::binary);
	ofs1.write((const char*)"abcd", strlen("abcd"));
	ofs1.close();

	std::ofstream ofs2("song1", std::ios::binary);
	ofs2.write((const char*)"kkkk", strlen("kkkk"));
	ofs2.close();

	Playlist p;
	p.addASong("Song 2", 0, 1, 55, "phtj", "song2");
	p.addASong("Song 1", 0, 1, 5, "p", "song1");
	
	p.printSongs();

	p.sortByName();
	p.printSongs();
	// Song 1, 00:01:05, Pop
	// Song 2, 00:01:55, Pop&Hip-hop&Techno&Jazz

	p.findSongPrint("Song 1");
	// Song 1, 00:01:05, Pop

	std::cout << std::endl;
	std::cout << "Result by genre: " << std::endl;
	p.printGetSongsByGenre('p');
	// Song 1, 00:01:05,  Pop
	// Song 2, 00:01:55, Pop&Hip-hop&Techno&Jazz

	p.printGetSongsByGenre('h');
	// Song 2, 00:01:55, Pop&Hip-hop&Techno&Jazz

	p.mix("Song 1", "Song 2");
	p.saveToBinaryFile("Song 1", "song3.dat");	
}


