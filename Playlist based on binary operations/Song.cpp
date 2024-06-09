#include "Song.h"

void Song::initContent()
{
	for (size_t i = 0; i < GlobalConstants::MAX_CONTENT; i++)
	{
		content[i] = 0;
	}
}
Song::Song()
{
	strcpy(this->name,"/0");
	genre = 0;  
	initContent();
	contentLength = 0;
    duration = 0;  
}

Song::Song(const char* songName, unsigned h, unsigned m, unsigned s, const char* genre, const char* fileName)
{
	setName(songName);
	setTime(h, m, s);
	setGenre(genre);
	readFromBinaryFile(fileName);
}

void Song::setName(const char* newName)
{
	if (!newName)
	{
		return;
	}
	strcpy(this->name, newName);
}

void Song::setTime(unsigned h, unsigned m, unsigned s)
{
	if (h >= 0 && m >= 0 && m <= 59 && s >= 0 && s <= 59)
	{
		duration = h * 3600 + m * 60 + s;
		return;
	}	
}

void Song::setBitFromStr(char chGenre)
{
	unsigned char mask = 1;
	switch (chGenre)
	{
	case 'r': this->genre |= 1;  break;
	case 'p': this->genre|=(mask<<1); break;
	case 'h': this->genre |= (mask << 2);  break;
	case 't': this->genre |= (mask << 3);  break;
	case 'j': this->genre |= (mask << 4); break;
	}
}

void Song::setGenre(const char* genre)    //rock = 1, pop = 2, hip-hop = 4, techno = 8, jazz = 16
{
	if (!genre)
	{
		return;
	}
	
	while (*genre)
	{
		setBitFromStr(*genre);
		genre++;
	}
}

const char* Song::getName() const
{
	return name;
}
unsigned Song::getDuration() const
{
	return duration;
}

bool Song::getIsValid() const
{
	return isValid;
}

char Song::getGenre() const
{
	return genre;
}

bool Song::addRythm(unsigned k)   
{
	unsigned buckIndex = k / 8;
	if (buckIndex > contentLength)
	{
		return false;
	}
	unsigned mask = 1;
	mask <<= (7-k + 1);
	content[buckIndex] |= mask; 
	return true;
}

void Song::mixWithAnotherSong(const Song& other) 
{
	size_t finalLen = std::min(this->contentLength, other.contentLength);

	for (size_t i = 0; i < finalLen; i++)   
	{
		this->content[i] ^= other.content[i];
	}
}

bool Song::saveToBinaryFile(std::ofstream& ofs) const
{
	ofs.write((const char*)content, contentLength);
	return true;
}

bool Song::saveToBinaryFile(const char* fileName) const
{
	if (!fileName)
	{
		return false;
	}
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return false;
	}
	saveToBinaryFile(ofs);
	ofs.close();
	return true;
}

bool Song::readFromBinaryFile(std::ifstream& ifs) 
{
	ifs.read((char*)content, contentLength);
	return true;
}

bool Song::readFromBinaryFile(const char* fileName) 
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return false;
	}
	readFromBinaryFile(ifs);
	ifs.close();
	return true;
}


bool Song::containsAGenre(char genre) const
{
	return (this->genre & genre);
}


void Song::printTime() const
{
	unsigned hours = duration / 3600;
	unsigned minutes = (duration / 60) % 60;
    unsigned seconds = duration % 60;
	std::cout << std::setw(2) << std::setfill('0') <<hours << ":"
		<< std::setw(2) << std::setfill('0') << minutes << ":"
		<< std::setw(2) << std::setfill('0') << seconds << " ";
}

void Song::printSongInfo()  const
{
	std::cout << name<<", ";
	printTime();	
	unsigned char mask = 1;
	if (genre & (mask))
	{
		std::cout<<"Rock ";
	}
	if (genre & (1 << 1))
	{
		std::cout<<"Pop ";
	}
	if (genre & (1 << 2))
	{
		std::cout << "Hip-hop ";
	}
	if (genre & (1 << 3))
	{
		std::cout << "Techno ";
	}
	if (genre & (1 << 4))
	{
		std::cout << "Jazz ";
	}
}


