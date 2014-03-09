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
	int numSongs;
	char songNames[NUMBER_OF_SONGS][LENGTH];	

	//have user 
	getDirectory(songNames, &numSongs);
	
	Song songs[numSongs];
	printf("here 1\n");

	int i;
	for (i = 0; i < numSongs; i++) {
		printf("here 1.5\n");
		songs[i].name =malloc(sizeof(char) * 10 ); 
		strcpy((songs[i].name), (songNames[i]));
		printf("here 1.57\n");
		songs[i].markov = (int *) calloc (numSongs, sizeof(int));
		songs[i].markovLength = numSongs;
	}
	printf("here 2\n");

	printSongs(songs, 3);

	//printf("%d", numSongs);

	//int i;
	//for (i = 0; i < numSongs; i++)
	//{
	//	printf("%s\n", songs[i]);
	//}


	Song arr[3];
	Song new, new2;
	
	//x.name = malloc ( sizeof(char) * 10 ); 	
	arr[0].name =malloc(sizeof(char) * 10 ); 
	arr[0].name = "markov";
	arr[0].markov =(int*) malloc( sizeof(int));
	*(arr[0].markov) = 10;
	*(arr[0].markov+1) = 4;

	arr[1].name = malloc ( sizeof(char) * 10 ); 
	arr[1].name = "Bryan";
	arr[1].markov =(int*) malloc( sizeof(int));
	*(arr[1].markov) = 7;
	*(arr[1].markov+1) = 4;

	arr[2].name = malloc ( sizeof(char) * 10 ); 
	arr[2].name = "Jerr";
	arr[2].markov =(int*) malloc( sizeof(int));
	*(arr[2].markov) = 9;
	*(arr[2].markov+1) = 4;

	writeBinarySongs(arr,3,"test.bin");

	Song arr2[3];
	readBinarySongs(arr2,3, "test.bin");
	printSongs(arr2, 3);
	
	/*FILE * data_file;
	data_file = fopen("test.bin", "wb");

	fwrite(&x, sizeof(Song), 1, data_file);
	fwrite(&y, sizeof(Song), 1, data_file);
	fclose(data_file);

	data_file = fopen("test.bin", "rb");
	fread(&new, sizeof(Song), 1, data_file);
	fread(&new2, sizeof(Song), 1, data_file);
	fclose(data_file);

	printf("name: %s", new.name);
	printf("number: %d", *(new.markov));
	printf("name: %s", new2.name);
	printf("number: %d", *(new2.markov));

*/
	return;
}



int getDirectory(char songs[NUMBER_OF_SONGS][LENGTH], int *songsAdded)
{
	char path[100];
	printf("Please enter the directory path with .mp3 files\n");
	fgets(path, 100, stdin);
	//printf("size: %d", strlen(path));
		
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

void writeBinarySongs(Song songs[], int numSongs, char fName[])
{

	FILE * data_file;
	int i;
	data_file = fopen(fName, "wb");

	for(i=0;i<numSongs;i++)
	{
		fwrite(&(songs[i]), sizeof(Song), 1, data_file);
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
		fread(&(songs[i]), sizeof(Song), 1, data_file);
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
