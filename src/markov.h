#include "song.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "loadFiles.h"

#ifndef MARKOV_H
#define MARKOV_H

extern Song * current;
extern Song * next;
extern Song * previous;

Song * getMostLikelySongs(Song songs[], int numSongs, Song song, int numReturn);
void insertValue(int * arr, int size, int value, int p);
Song * makeExampleSongs();
void testInsertValue();
void testLikelySongs();
int randLim(int limit);
Song * getNextSong(Song *song);

#endif
