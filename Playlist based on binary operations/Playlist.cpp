#include "Playlist.h"

void Playlist::sortPlaylist(bool(*isLess)(const Song& lhs, const Song& rhs))
{
    for (int i = 0; i < songsCount; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < songsCount; j++)
        {
            if (isLess(songs[j], songs[minIndex]))
            {
                minIndex = j;
            }

        }
        if (i != minIndex)
        {
            std::swap(songs[i], songs[minIndex]);
        }
    }
}

void Playlist::sortByName()
{
    return sortPlaylist([](const Song& lhs, const Song& rhs) { return strcmp(lhs.getName(), rhs.getName()) < 0; });
}
void Playlist::sortByDuration()
{
    return sortPlaylist([](const Song& lhs, const Song& rhs) { return lhs.getDuration() < rhs.getDuration(); });
}

bool Playlist::addASong(const char* songName, unsigned h, unsigned m, unsigned s, const char* genre, const char* fileName)
{
    if (songsCount >= MAX_SONGS)
    {
        return false;
    }
    Song newSong(songName, h, m, s,  genre, fileName);
    if (!newSong.getIsValid())
    {
        return false;
    }    
    songs[songsCount++] = newSong;
    return true;
}


void Playlist::printSongs() const
{
    for (size_t i = 0; i < songsCount; i++)
    {
        songs[i].printSongInfo();
        std::cout<<std::endl;
    }    
}

int Playlist::findSong(const char* songName) const
{
    if (!songName)
    {
        return -1;
    }
    for (size_t i = 0; i < songsCount; i++)
    {
        if (strcmp(songs[i].getName(), songName)==0)
        {
            return i;
        }
    }
    return -1;
}

unsigned char getGenre(unsigned char genre)
{
    char currentG = 0;
    unsigned char mask = 1;
    currentG |= (mask << getBitFromStr(genre));    
    return currentG;
}

void Playlist::printGetSongsByGenre(unsigned char genre) const
{
    char currentG = getGenre(genre);
    for (size_t i = 0; i < songsCount; i++)
    {
        if (songs[i].containsAGenre(currentG))
        {
            songs[i].printSongInfo();
            std::cout << std::endl;
        }         
    }   
}


bool Playlist::addRythm(const char* songName, unsigned k)
{
    int songIndex = findSong(songName);
    if (songIndex < 0)
    {
        return false;
    }
    return songs[songIndex].addRythm(k);
}

bool Playlist::mix(const char* firstSong, const char* secondSong)
{
    int index1 = findSong(firstSong);
    int index2 = findSong(firstSong);

    if (index1 < 0 || index2<0)
    {
        return false;
    }
    songs[index1].mixWithAnotherSong(songs[index2]);
    return true;
}

bool Playlist::saveToBinaryFile(const char* songName, const char* fileName) const
{
    int songIndex = findSong(songName);
    if (songIndex < 0)
    {
        return false;
    }
    return songs[songIndex].saveToBinaryFile(fileName);
}

void Playlist::findSongPrint(const char* songName) const
{
    int songIndex = findSong(songName);
    if (songIndex < 0)
    {
       std::cout<<"No such song!";
    }
    songs[songIndex].printSongInfo();
}