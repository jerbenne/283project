#include <stdlib.h>
#include <string.h>

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

#endif
