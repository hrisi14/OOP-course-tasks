#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <iomanip>
#include "Utils.h"
#pragma warning( disable : 4996 )

namespace GlobalConstants
{
	constexpr size_t MAX_LEN_NAME = 64;
	constexpr size_t MAX_CONTENT = 256;
	constexpr size_t MAX_LEN_GENRE = 50;
}

class Song
{
	char name[GlobalConstants::MAX_LEN_NAME] = "/0";
	unsigned char genre = 0;  
	unsigned char content[GlobalConstants::MAX_CONTENT];   
	size_t contentLength = 0;
	unsigned duration = 0;   //in seconds
	bool isValid = true;
	
public:
	Song();
	Song(const char* songName, unsigned h, unsigned m, unsigned s, const char* genre, const char* fileName);
	void setName(const char* newName);
	void setTime(unsigned h, unsigned m, unsigned s);
	void setGenre(const char* genre);
	
	void initContent();
	const char* getName() const;
	unsigned getDuration() const;
	bool getIsValid() const;
	char getGenre() const;
	bool addRythm(unsigned k);    
	void mixWithAnotherSong(const Song& other);  

	bool saveToBinaryFile(std::ofstream& ofs) const;
	bool saveToBinaryFile(const char* fileName) const;

	bool readFromBinaryFile(std::ifstream& ifs);
	bool readFromBinaryFile(const char* fileName);

	bool containsAGenre(char genre) const;
	void printTime() const;  //a function by angeld55-Time.cpp
	void printSongInfo() const;
	
	void setBitFromStr(char chGenre);
};

