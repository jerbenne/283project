#include <stdlib.h>
#include <string.h>
//define song struct
//access song->markov[i]
typedef struct Song {
	   int nameLength;
	   int markovLength;
	   char *name;
	   int *markov;
}Song;
