#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "song.h"

#include <dirent.h>

#define NUMBER_OF_SONGS 100
#define LENGTH 40

pid_t pid;
void catchint(int sig);
int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded);
void writeBinarySongs(Song songs[], int numSongs, char fName[]);
void readBinarySongs(Song songs[], int numSongs, char fName[]);
void printSongs(Song songs[], int numSongs);
void initializeSongs(Song songs[], int numSongs, char songNames[][LENGTH]);


int compare(const void *one, const void *two)
{

            return (strcmp(*(char **)one, *(char **)two));
}

main(int argc, char * argv[])
{

	//if((pid = fork()) == 0)
	//{
	//	setpgid(0,0);
		//execvp(argv[1], &argv[1]);
		//execvp(argv[1], argv);
	//	  execvp("mpg123", argv);
	//}

	//signal(SIGINT, catchint);
	//int status;
	//if (waitpid(pid, &status, 0) < 0)
	//	printf("waitfg: waitpid error");


	//array of songs
	int numSongs = 3;
	char songNames[NUMBER_OF_SONGS][LENGTH];	

	//have user 
	getDirectory(songNames, &numSongs);
	Song songs[numSongs];
	Song songs2[numSongs];

	//char input;
	//printf("Is this your first time? y/n\n");
	//input = fgetc(stdin);


	//if (input == 'y') {
	
		//initializeSongs(songs, numSongs, songNames);
		printf("here1\n");
		//writeBinarySongs(songs, numSongs, "t1.bin");
		//printf("here2\n");
		//printSongs(songs,numSongs);
		//printf("delete some songs\n");
		//strcpy(songs[2].name,"songName");

//	}
//	else {
		numSongs = 3;
		readBinarySongs(songs2, numSongs, "t1.bin");
		printf("here4\n");
	//}

	printSongs(songs2, numSongs);

	return;
}



int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded)
{
	char path[100];
	printf("Please enter the directory path with .mp3 files\n");
	//fgets(path, 100, stdin);
	//printf("size: %d", strlen(path));
	 strcpy(path, "/home/jab489/Music");	
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

void initializeSongs(Song songs[], int numSongs, char songNames[][LENGTH])
{

	int i;
	for (i = 0; i < numSongs; i++) {
		songs[i].name =malloc(sizeof(char) * (strlen(songNames[i]) + 1) ); 
		strcpy((songs[i].name), (songNames[i]));
		songs[i].markov = (int *) calloc (numSongs, sizeof(int));
		songs[i].markovLength = numSongs;
		songs[i].nameLength = strlen(songs[i].name) + 1;

	}
	
}

void writeBinarySongs(Song songs[], int numSongs, char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "wb");

	for(i=0;i<numSongs;i++)
	{
		//TODO: make it so it saves each data member
		//      dynamically.
		fwrite(&songs[i].nameLength, sizeof(int), 1, data_file);
		fwrite(&songs[i].markovLength, sizeof(int), 1, data_file);
		int j;
		//for(j= 0; j < songs[i].nameLength; j++)
		//	fwrite(songs[i].name[j], sizeof(char), 1, data_file);
		printf("hereeee\n");
		fwrite(songs[i].name, sizeof(char), songs[i].nameLength, data_file);
		fwrite(songs[i].markov, sizeof(int), songs[i].markovLength, data_file);
	}
	fclose(data_file);
	
}

void readBinarySongs(Song songs[], int numSongs, char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "rb");

	for(i=0;i<numSongs;i++)
	{
		fread(&songs[i].nameLength, sizeof(int), 1, data_file);
		fread(&songs[i].markovLength, sizeof(int), 1, data_file);
		printf("%d %d\n", songs[i].nameLength, songs[i].markovLength);
		songs[i].name = malloc( sizeof(char) * songs[i].nameLength);
		songs[i].markov = malloc( sizeof(int) * songs[i].markovLength);
		printf("here3\n");
		//strcpy(songs[i].name, "test");
		//*(songs[i].markov) = 5;
		//char * test = (char *) malloc(sizeof(char) * 50);
		//fread(test, sizeof(char), songs[i].nameLength, data_file);
		//printf("%c%c\n", test[0],test[1]);
		
		//printf("%s\n", test);
		fread(songs[i].name, sizeof(char), songs[i].nameLength, data_file);
		fread(songs[i].markov, sizeof(int), songs[i].markovLength, data_file);
		//printf("%s\n", songs[i].name);
		//fread(&(songs[i]), sizeof(Song), 1, data_file);
	}
	fclose(data_file);
	
}

void printSongs(Song songs[], int numSongs)
{
	int i;
	for(i=0;i<numSongs;i++)
	{
		printf("song[%d] name: %s\n",i,songs[i].name);
		int j;
		for (j = 0; j < songs[i].markovLength; j++)
			printf("song[%d] markov: %d\n",i,songs[i].markov[j]);
	}
}

void catchint (int sig) {	

	printf("Do you want to quit program?!\n");
	char input[100];
	fgets(input, 100, stdin);	

	if( strcmp(input, "yes"))
	{
		kill(pid, SIGINT);
		exit(0);
	}
	else
		return;
	
}
