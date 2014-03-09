#include <stdlib.h>
#include <string.h>
//define song struct
//access song->markov[i]
typedef struct Song {
	   char *name;
	   int *markov;
       int markovLength;
}Song;
