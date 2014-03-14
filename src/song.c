#include "song.h"


void printAllSongs()
{
	printf("Songs:%s\n%d", songList[0].name, numSongs);
	int i;
	for(i=0;i<numSongs;i++)
	{
		printf("song[%d] name: %s\n",i,songList[i].name);
		int j;
		for (j = 0; j < songList[i].markovLength; j++)
			printf("song[%d] markov[%d]: %d\n",i,j,songList[i].markov[j]);
	}
}

void printSongs(Song * songs, int n)
{
	printf("Songs:%s\n%d", songs[0].name, n);
	int i;
	for(i=0;i<n;i++)
	{
		printf("song[%d] name: %s\n",i,songs[i].name);
		int j;
		for (j = 0; j < songs[i].markovLength; j++)
			printf("song[%d] markov[%d]: %d\n",i,j,songs[i].markov[j]);
	}
}

//return the location in song list of a song
int songToId(Song * song) {
    int i;
    for (i=0;i<numSongs;i++) {
        if(strcmp(song->name,songList[i].name))
            return i;
    }
    return -1;
}

Song * getSongByString(char * str) {
    int i;
    for(i=0;i<numSongs;i++) {
        if(strcmp(str,songList[i].name))
            return &songList[i];
    }
    return NULL;
}
