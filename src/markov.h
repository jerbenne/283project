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
extern Song * songList;
extern int numSongs;

Song * getMostLikelySongs(Song * song, int numReturn);
void insertValue(int * arr, int size, int value, int p);
int randLim(int limit);
Song * getNextSong(Song *song);
void peek(int x);
int getTotalSongsChained(Song *song);

#endif
