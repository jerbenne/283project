#include "loadFiles.h"


//TODO: NUMBER_OF_SONGS is bad
#define NUMBER_OF_SONGS 300
#define LENGTH 40
#define MAXLINE 100
#define MAXARGS 5

extern char * path;


void writeBinarySongs(int numSongs, char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "wb");

	/* Write number of songs */
	fwrite(&numSongs, sizeof(int), 1, data_file);
	
	int directoryChars = strlen(path) + 1;

	/* Write length of directory */
	fwrite( &directoryChars , sizeof(int), 1, data_file);

	/* Write directory path */
	fwrite(path, sizeof(char), strlen(path) + 1, data_file);

	/* Write all songs*/
	for(i=0;i<numSongs;i++)
	{
		//TODO: make it so it saves each data member
		//      dynamically.
		fwrite(&songList[i].nameLength, sizeof(int), 1, data_file);
		fwrite(&songList[i].markovLength, sizeof(int), 1, data_file);
		int j;
		//for(j= 0; j < songs[i].nameLength; j++)
		//	fwrite(songs[i].name[j], sizeof(char), 1, data_file);
		printf("here\n");
		fwrite(songList[i].name, sizeof(char), songList[i].nameLength, data_file);
		fwrite(songList[i].markov, sizeof(int), songList[i].markovLength, data_file);
	}
	fclose(data_file);
	
}

int readBinarySongs(char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "rb");

	/* Read in number of songs */
	int numSongs;
	fread(&numSongs, sizeof(int), 1, data_file);
	printf("songs: %d\n", numSongs);

	songList = (Song *) malloc ( sizeof(Song) * numSongs);

	/* Read in length of directory */
	int directoryLength;
	fread(&directoryLength, sizeof(int), 1, data_file);
	printf("directory length: %d\n", directoryLength);

	/* Read in directory path */
	path = (char *) malloc( sizeof(char) * 100);
	fread(path, sizeof(char), directoryLength, data_file);
	printf("path: %s\n", path);

	for(i=0;i<numSongs;i++)
	{
		fread(&songList[i].nameLength, sizeof(int), 1, data_file);
		fread(&songList[i].markovLength, sizeof(int), 1, data_file);
		printf("%d %d\n", songList[i].nameLength, songList[i].markovLength);
		songList[i].name = malloc( sizeof(char) * songList[i].nameLength);
		songList[i].markov = malloc( sizeof(int) * songList[i].markovLength);
		
		fread(songList[i].name, sizeof(char), songList[i].nameLength, data_file);
		fread(songList[i].markov, sizeof(int), songList[i].markovLength, data_file);
	}
	fclose(data_file);
	
	return numSongs;
}


void initializeSongs(int numSongs, char songNames[][LENGTH])
{

	int i,j;
	songList = (Song *) malloc ( sizeof(Song) * numSongs);

	for (i = 0; i < numSongs; i++) {
		songList[i].name =malloc(sizeof(char) * (strlen(songNames[i]) + 1) ); 
		strcpy((songList[i].name), (songNames[i]));
		songList[i].markov = (int *) calloc (numSongs, sizeof(int));
		for (j = 0; j < numSongs; j++)
			songList[i].markov[j] = 1;
		songList[i].markovLength = numSongs;
		songList[i].nameLength = strlen(songList[i].name) + 1;

	}
	
}

//TODO: fix this function
int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded)
{
	printf("Please enter the directory path with .mp3 files\n");
	path = (char *) malloc( sizeof(char) * 100);
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
