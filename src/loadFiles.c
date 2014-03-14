#include "loadFiles.h"


//TODO: NUMBER_OF_SONGS is bad
#define NUMBER_OF_SONGS 300
#define LENGTH 40
#define MAXLINE 100
#define MAXARGS 5

void printSongs(Song songs[], int numSongs)
{
	int i;
	for(i=0;i<numSongs;i++)
	{
		printf("song[%d] name: %s\n",i,songs[i].name);
		int j;
		for (j = 0; j < songs[i].markovLength; j++)
			printf("song[%d] markov[%d]: %d\n",i,j,songs[i].markov[j]);
	}
}

void writeBinarySongs(Song songs[], int numSongs, char fName[], char directory[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "wb");

	/* Write number of songs */
	fwrite(&numSongs, sizeof(int), 1, data_file);
	
	int directoryChars = strlen(directory) + 1;

	/* Write length of directory */
	fwrite( &directoryChars , sizeof(int), 1, data_file);

	/* Write directory path */
	fwrite(directory, sizeof(char), strlen(directory) + 1, data_file);

	/* Write all songs*/
	for(i=0;i<numSongs;i++)
	{
		//TODO: make it so it saves each data member
		//      dynamically.
		fwrite(&songs[i].nameLength, sizeof(int), 1, data_file);
		fwrite(&songs[i].markovLength, sizeof(int), 1, data_file);
		int j;
		//for(j= 0; j < songs[i].nameLength; j++)
		//	fwrite(songs[i].name[j], sizeof(char), 1, data_file);
		printf("here\n");
		fwrite(songs[i].name, sizeof(char), songs[i].nameLength, data_file);
		fwrite(songs[i].markov, sizeof(int), songs[i].markovLength, data_file);
	}
	fclose(data_file);
	
}

void readBinarySongs(Song songs[], char fName[], char directoryPath[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "rb");

	/* Read in number of songs */
	int numSongs;
	fread(&numSongs, sizeof(int), 1, data_file);
	printf("songs: %d\n", numSongs);

	/* Read in length of directory */
	int directoryLength;
	fread(&directoryLength, sizeof(int), 1, data_file);
	printf("directory length: %d\n", directoryLength);

	/* Read in directory path */
	fread(directoryPath, sizeof(char), directoryLength, data_file);
	

	for(i=0;i<numSongs;i++)
	{
		fread(&songs[i].nameLength, sizeof(int), 1, data_file);
		fread(&songs[i].markovLength, sizeof(int), 1, data_file);
		printf("%d %d\n", songs[i].nameLength, songs[i].markovLength);
		songs[i].name = malloc( sizeof(char) * songs[i].nameLength);
		songs[i].markov = malloc( sizeof(int) * songs[i].markovLength);
		
		fread(songs[i].name, sizeof(char), songs[i].nameLength, data_file);
		fread(songs[i].markov, sizeof(int), songs[i].markovLength, data_file);
	}
	fclose(data_file);
	
}


void initializeSongs(Song songs[], int numSongs, char songNames[][LENGTH])
{

	int i,j;
	for (i = 0; i < numSongs; i++) {
		songs[i].name =malloc(sizeof(char) * (strlen(songNames[i]) + 1) ); 
		strcpy((songs[i].name), (songNames[i]));
		songs[i].markov = (int *) calloc (numSongs, sizeof(int));
		for (j = 0; j < numSongs; j++)
			songs[i].markov[j] = 1;
		songs[i].markovLength = numSongs;
		songs[i].nameLength = strlen(songs[i].name) + 1;

	}
	
}

int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded, char path[])
{
	printf("Please enter the directory path with .mp3 files\n");
	fgets(path, 100, stdin);
	//printf("size: %d", strlen(path));
	//strcpy(path, "/home/jab489/Music");	
	strtok(path, "\n");
	DIR *dp; //pointer to directory
	struct dirent *ep; // directory entry

	int songNumber = 0;

	if((dp = opendir(path)) == NULL) {
		printf("cant open %s\n", path);
		return(0);
	}
	//type 8 is mp3
	else {
		while ((ep = readdir(dp)) != NULL) {
			if (ep->d_type == 8) {
				strcpy(songs[songNumber], ep->d_name);
				songNumber++;
			}
		}
	}

	*songsAdded = songNumber;
	qsort(songs, songNumber, LENGTH,
		(int (*)(const void *, const void*)) strcmp);

}
