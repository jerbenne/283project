#include "song.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#ifndef LOADFILES_H
#define LOADFILES_H

//TODO: NUMBER_OF_SONGS is bad
#define NUMBER_OF_SONGS 300
#define LENGTH 40


void printSongs(Song songs[], int numSongs);
void writeBinarySongs(Song songs[], int numSongs, char fName[], char directory[]);
void readBinarySongs(Song songs[], char fName[], char directoryPath[]);
int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded, char path[]);
void initializeSongs(Song songs[], int numSongs, char songNames[][LENGTH]);



#endif
