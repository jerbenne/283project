#include "song.h"

#ifndef MARKOV_H
#define MARKOV_H

Song * getMostLikelySongs(Song songs[], int numSongs, Song song, int numReturn);
void insertValue(int * arr, int size, int value, int p);
Song * makeExampleSongs();
void testInsertValue();
void testLikelySongs();
int randLim(int limit);
Song * getNextSong(Song songs[], int numSongs, Song currentSong);
int songToId(Song * song);

#endif
