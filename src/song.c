#include "song.h"

/**
 * prints song id, name, and markov chains for all songs
 */
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

/**
 * prints song id, name, and markov chains for all songs in list songs with
 * length n
 */
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

/**
 * returns song id given a pointer to a Song struct
 * song id is used in songList and markov chains
 */
int songToId(Song * song) {
    int i;
    for (i=0;i<numSongs;i++) {
        if(strcmp(song->name,songList[i].name)==0)
            return i;
    }
    printf("error: songToId, song not found\n");
    return -1;
}
/**
 * returns pointer to song struct given a song name
 */
Song * getSongByString(char * str) {
    int i;
    for(i=0;i<numSongs;i++) {
		//printf("%d: %s\n", i, songList[i].name);
        if(strcmp(str,songList[i].name)==0)
            return &songList[i];
    }
    return NULL;
}
/**
 * prints previous, current, and next song
 */
void printStatus() {
	printf("Previous: %s\n", (previous!=NULL) ? previous->name : "None");
	printf("Current: %s\n", (current!=NULL) ? current->name : "None");
	printf("Next: %s\n", (next!=NULL) ? next->name : "None");
}
