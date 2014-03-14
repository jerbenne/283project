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
extern Song * current;
extern Song * next;
extern Song * previous;

int songToId(Song * song);
void printAllSongs();
void printSongs(Song * songs, int n);
Song * getSongByString(char * str);
void printStatus();

#endif
