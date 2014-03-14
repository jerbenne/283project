#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef SONG_H
#define SONG_H

//define song struct
//access song->markov[i]
typedef struct Song {
	   int nameLength;
	   int markovLength;
	   char *name;
	   int *markov;
}Song;

extern Song * songList;
extern int numSongs;

int songToId(Song * song);
void printAllSongs();
void printSongs(Song * songs, int n);

#endif
